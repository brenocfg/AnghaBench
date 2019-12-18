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
struct synquacer_i2c {int state; int /*<<< orphan*/  pclkrate; int /*<<< orphan*/  dev; TYPE_1__* msg; int /*<<< orphan*/  msg_idx; int /*<<< orphan*/  msg_ptr; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; unsigned char* buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  STATE_READ 130 
#define  STATE_START 129 
#define  STATE_WRITE 128 
 unsigned char SYNQUACER_I2C_BCR_ACK ; 
 unsigned char SYNQUACER_I2C_BCR_BEIE ; 
 unsigned char SYNQUACER_I2C_BCR_BER ; 
 unsigned char SYNQUACER_I2C_BCR_INTE ; 
 unsigned char SYNQUACER_I2C_BCR_MSS ; 
 unsigned char SYNQUACER_I2C_BSR_AL ; 
 unsigned char SYNQUACER_I2C_BSR_FBT ; 
 unsigned char SYNQUACER_I2C_BSR_LRB ; 
 scalar_t__ SYNQUACER_I2C_REG_BCR ; 
 scalar_t__ SYNQUACER_I2C_REG_BSR ; 
 scalar_t__ SYNQUACER_I2C_REG_DAR ; 
 int /*<<< orphan*/  WAIT_PCLK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  is_lastmsg (struct synquacer_i2c*) ; 
 int /*<<< orphan*/  is_msgend (struct synquacer_i2c*) ; 
 int /*<<< orphan*/  is_msglast (struct synquacer_i2c*) ; 
 unsigned char readb (scalar_t__) ; 
 int synquacer_i2c_master_start (struct synquacer_i2c*,TYPE_1__*) ; 
 int /*<<< orphan*/  synquacer_i2c_stop (struct synquacer_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static irqreturn_t synquacer_i2c_isr(int irq, void *dev_id)
{
	struct synquacer_i2c *i2c = dev_id;

	unsigned char byte;
	unsigned char bsr, bcr;
	int ret;

	bcr = readb(i2c->base + SYNQUACER_I2C_REG_BCR);
	bsr = readb(i2c->base + SYNQUACER_I2C_REG_BSR);
	dev_dbg(i2c->dev, "bsr:0x%02x, bcr:0x%02x\n", bsr, bcr);

	if (bcr & SYNQUACER_I2C_BCR_BER) {
		dev_err(i2c->dev, "bus error\n");
		synquacer_i2c_stop(i2c, -EAGAIN);
		goto out;
	}
	if ((bsr & SYNQUACER_I2C_BSR_AL) ||
	    !(bcr & SYNQUACER_I2C_BCR_MSS)) {
		dev_dbg(i2c->dev, "arbitration lost\n");
		synquacer_i2c_stop(i2c, -EAGAIN);
		goto out;
	}

	switch (i2c->state) {
	case STATE_START:
		if (bsr & SYNQUACER_I2C_BSR_LRB) {
			dev_dbg(i2c->dev, "ack was not received\n");
			synquacer_i2c_stop(i2c, -EAGAIN);
			goto out;
		}

		if (i2c->msg->flags & I2C_M_RD)
			i2c->state = STATE_READ;
		else
			i2c->state = STATE_WRITE;

		if (is_lastmsg(i2c) && i2c->msg->len == 0) {
			synquacer_i2c_stop(i2c, 0);
			goto out;
		}

		if (i2c->state == STATE_READ)
			goto prepare_read;

		/* fall through */

	case STATE_WRITE:
		if (bsr & SYNQUACER_I2C_BSR_LRB) {
			dev_dbg(i2c->dev, "WRITE: No Ack\n");
			synquacer_i2c_stop(i2c, -EAGAIN);
			goto out;
		}

		if (!is_msgend(i2c)) {
			writeb(i2c->msg->buf[i2c->msg_ptr++],
			       i2c->base + SYNQUACER_I2C_REG_DAR);

			/* clear IRQ, and continue */
			writeb(SYNQUACER_I2C_BCR_BEIE |
			       SYNQUACER_I2C_BCR_MSS |
			       SYNQUACER_I2C_BCR_INTE,
			       i2c->base + SYNQUACER_I2C_REG_BCR);
			break;
		}
		if (is_lastmsg(i2c)) {
			synquacer_i2c_stop(i2c, 0);
			break;
		}
		dev_dbg(i2c->dev, "WRITE: Next Message\n");

		i2c->msg_ptr = 0;
		i2c->msg_idx++;
		i2c->msg++;

		/* send the new start */
		ret = synquacer_i2c_master_start(i2c, i2c->msg);
		if (ret < 0) {
			dev_dbg(i2c->dev, "restart error (%d)\n", ret);
			synquacer_i2c_stop(i2c, -EAGAIN);
			break;
		}
		i2c->state = STATE_START;
		break;

	case STATE_READ:
		byte = readb(i2c->base + SYNQUACER_I2C_REG_DAR);
		if (!(bsr & SYNQUACER_I2C_BSR_FBT)) /* data */
			i2c->msg->buf[i2c->msg_ptr++] = byte;
		else /* address */
			dev_dbg(i2c->dev, "address:0x%02x. ignore it.\n", byte);

prepare_read:
		if (is_msglast(i2c)) {
			writeb(SYNQUACER_I2C_BCR_MSS |
			       SYNQUACER_I2C_BCR_BEIE |
			       SYNQUACER_I2C_BCR_INTE,
			       i2c->base + SYNQUACER_I2C_REG_BCR);
			break;
		}
		if (!is_msgend(i2c)) {
			writeb(SYNQUACER_I2C_BCR_MSS |
			       SYNQUACER_I2C_BCR_BEIE |
			       SYNQUACER_I2C_BCR_INTE |
			       SYNQUACER_I2C_BCR_ACK,
			       i2c->base + SYNQUACER_I2C_REG_BCR);
			break;
		}
		if (is_lastmsg(i2c)) {
			/* last message, send stop and complete */
			dev_dbg(i2c->dev, "READ: Send Stop\n");
			synquacer_i2c_stop(i2c, 0);
			break;
		}
		dev_dbg(i2c->dev, "READ: Next Transfer\n");

		i2c->msg_ptr = 0;
		i2c->msg_idx++;
		i2c->msg++;

		ret = synquacer_i2c_master_start(i2c, i2c->msg);
		if (ret < 0) {
			dev_dbg(i2c->dev, "restart error (%d)\n", ret);
			synquacer_i2c_stop(i2c, -EAGAIN);
		} else {
			i2c->state = STATE_START;
		}
		break;
	default:
		dev_err(i2c->dev, "called in err STATE (%d)\n", i2c->state);
		break;
	}

out:
	WAIT_PCLK(10, i2c->pclkrate);
	return IRQ_HANDLED;
}