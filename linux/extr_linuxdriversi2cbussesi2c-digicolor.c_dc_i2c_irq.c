#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dc_i2c {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; TYPE_1__* msg; int /*<<< orphan*/  msgbuf_ptr; int /*<<< orphan*/  error; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int I2C_M_RD ; 
 int II_CMD_STATUS_ABORT ; 
 int II_CMD_STATUS_ACK_BAD ; 
 scalar_t__ II_INTFLAG_CLEAR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  STATE_ADDR 132 
 int STATE_IDLE ; 
#define  STATE_READ 131 
#define  STATE_START 130 
#define  STATE_STOP 129 
#define  STATE_WRITE 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dc_i2c_addr_cmd (TYPE_1__*) ; 
 int dc_i2c_cmd_status (struct dc_i2c*) ; 
 int /*<<< orphan*/  dc_i2c_next_read (struct dc_i2c*) ; 
 int /*<<< orphan*/  dc_i2c_read_buf (struct dc_i2c*) ; 
 int /*<<< orphan*/  dc_i2c_stop (struct dc_i2c*) ; 
 int /*<<< orphan*/  dc_i2c_write_buf (struct dc_i2c*) ; 
 int /*<<< orphan*/  dc_i2c_write_byte (struct dc_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t dc_i2c_irq(int irq, void *dev_id)
{
	struct dc_i2c *i2c = dev_id;
	int cmd_status = dc_i2c_cmd_status(i2c);
	unsigned long flags;
	u8 addr_cmd;

	writeb_relaxed(1, i2c->regs + II_INTFLAG_CLEAR);

	spin_lock_irqsave(&i2c->lock, flags);

	if (cmd_status == II_CMD_STATUS_ACK_BAD
	    || cmd_status == II_CMD_STATUS_ABORT) {
		i2c->error = -EIO;
		complete(&i2c->done);
		goto out;
	}

	switch (i2c->state) {
	case STATE_START:
		addr_cmd = dc_i2c_addr_cmd(i2c->msg);
		dc_i2c_write_byte(i2c, addr_cmd);
		i2c->state = STATE_ADDR;
		break;
	case STATE_ADDR:
		if (i2c->msg->flags & I2C_M_RD) {
			dc_i2c_next_read(i2c);
			i2c->state = STATE_READ;
			break;
		}
		i2c->state = STATE_WRITE;
		/* fall through */
	case STATE_WRITE:
		if (i2c->msgbuf_ptr < i2c->msg->len)
			dc_i2c_write_buf(i2c);
		else
			dc_i2c_stop(i2c);
		break;
	case STATE_READ:
		if (i2c->msgbuf_ptr < i2c->msg->len)
			dc_i2c_read_buf(i2c);
		else
			dc_i2c_stop(i2c);
		break;
	case STATE_STOP:
		i2c->state = STATE_IDLE;
		complete(&i2c->done);
		break;
	}

out:
	spin_unlock_irqrestore(&i2c->lock, flags);
	return IRQ_HANDLED;
}