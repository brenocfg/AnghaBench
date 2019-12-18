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
struct sh_mobile_i2c_data {size_t pos; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  send_stop; TYPE_1__* msg; } ;
typedef  enum sh_mobile_i2c_op { ____Placeholder_sh_mobile_i2c_op } sh_mobile_i2c_op ;
struct TYPE_2__ {int* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICCR ; 
 int ICCR_BBSY ; 
 int ICCR_ICE ; 
 int ICCR_RACK ; 
 int ICCR_SCP ; 
 int ICCR_TRS ; 
 int /*<<< orphan*/  ICDR ; 
 int /*<<< orphan*/  ICIC ; 
 int ICIC_ALE ; 
 int ICIC_DTEE ; 
 int ICIC_TACKE ; 
 int ICIC_WAITE ; 
#define  OP_RX 135 
#define  OP_RX_STOP 134 
#define  OP_RX_STOP_DATA 133 
#define  OP_START 132 
#define  OP_TX 131 
#define  OP_TX_FIRST 130 
#define  OP_TX_STOP 129 
#define  OP_TX_TO_RX 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int i2c_8bit_addr_from_msg (TYPE_1__*) ; 
 unsigned char iic_rd (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iic_wr (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char i2c_op(struct sh_mobile_i2c_data *pd, enum sh_mobile_i2c_op op)
{
	unsigned char ret = 0;
	unsigned long flags;

	dev_dbg(pd->dev, "op %d\n", op);

	spin_lock_irqsave(&pd->lock, flags);

	switch (op) {
	case OP_START: /* issue start and trigger DTE interrupt */
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_TRS | ICCR_BBSY);
		break;
	case OP_TX_FIRST: /* disable DTE interrupt and write client address */
		iic_wr(pd, ICIC, ICIC_WAITE | ICIC_ALE | ICIC_TACKE);
		iic_wr(pd, ICDR, i2c_8bit_addr_from_msg(pd->msg));
		break;
	case OP_TX: /* write data */
		iic_wr(pd, ICDR, pd->msg->buf[pd->pos]);
		break;
	case OP_TX_STOP: /* issue a stop (or rep_start) */
		iic_wr(pd, ICCR, pd->send_stop ? ICCR_ICE | ICCR_TRS
					       : ICCR_ICE | ICCR_TRS | ICCR_BBSY);
		break;
	case OP_TX_TO_RX: /* select read mode */
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_SCP);
		break;
	case OP_RX: /* just read data */
		ret = iic_rd(pd, ICDR);
		break;
	case OP_RX_STOP: /* enable DTE interrupt, issue stop */
		iic_wr(pd, ICIC,
		       ICIC_DTEE | ICIC_WAITE | ICIC_ALE | ICIC_TACKE);
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_RACK);
		break;
	case OP_RX_STOP_DATA: /* enable DTE interrupt, read data, issue stop */
		iic_wr(pd, ICIC,
		       ICIC_DTEE | ICIC_WAITE | ICIC_ALE | ICIC_TACKE);
		ret = iic_rd(pd, ICDR);
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_RACK);
		break;
	}

	spin_unlock_irqrestore(&pd->lock, flags);

	dev_dbg(pd->dev, "op %d, data out 0x%02x\n", op, ret);
	return ret;
}