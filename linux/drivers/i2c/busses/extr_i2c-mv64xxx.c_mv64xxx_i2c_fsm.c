#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct mv64xxx_i2c_data {scalar_t__ state; int bytes_left; int /*<<< orphan*/  rc; void* action; TYPE_2__* msg; TYPE_1__ adapter; int /*<<< orphan*/  cntl_bits; int /*<<< orphan*/  aborting; int /*<<< orphan*/  send_stop; int /*<<< orphan*/  byte_posn; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENXIO ; 
 int I2C_M_TEN ; 
 void* MV64XXX_I2C_ACTION_CONTINUE ; 
 void* MV64XXX_I2C_ACTION_RCV_DATA ; 
 void* MV64XXX_I2C_ACTION_RCV_DATA_STOP ; 
 void* MV64XXX_I2C_ACTION_SEND_ADDR_1 ; 
 void* MV64XXX_I2C_ACTION_SEND_ADDR_2 ; 
 void* MV64XXX_I2C_ACTION_SEND_DATA ; 
 void* MV64XXX_I2C_ACTION_SEND_RESTART ; 
 void* MV64XXX_I2C_ACTION_SEND_STOP ; 
 int /*<<< orphan*/  MV64XXX_I2C_REG_CONTROL_ACK ; 
 scalar_t__ MV64XXX_I2C_STATE_IDLE ; 
 scalar_t__ MV64XXX_I2C_STATE_WAITING_FOR_ADDR_1_ACK ; 
 void* MV64XXX_I2C_STATE_WAITING_FOR_ADDR_2_ACK ; 
 scalar_t__ MV64XXX_I2C_STATE_WAITING_FOR_RESTART ; 
 scalar_t__ MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_ACK ; 
 scalar_t__ MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_DATA ; 
#define  MV64XXX_I2C_STATUS_MAST_RD_ADDR_2_ACK 139 
#define  MV64XXX_I2C_STATUS_MAST_RD_ADDR_ACK 138 
#define  MV64XXX_I2C_STATUS_MAST_RD_ADDR_NO_ACK 137 
#define  MV64XXX_I2C_STATUS_MAST_RD_DATA_ACK 136 
#define  MV64XXX_I2C_STATUS_MAST_RD_DATA_NO_ACK 135 
#define  MV64XXX_I2C_STATUS_MAST_REPEAT_START 134 
#define  MV64XXX_I2C_STATUS_MAST_START 133 
#define  MV64XXX_I2C_STATUS_MAST_WR_ACK 132 
#define  MV64XXX_I2C_STATUS_MAST_WR_ADDR_2_ACK 131 
#define  MV64XXX_I2C_STATUS_MAST_WR_ADDR_ACK 130 
#define  MV64XXX_I2C_STATUS_MAST_WR_ADDR_NO_ACK 129 
#define  MV64XXX_I2C_STATUS_MAST_WR_NO_ACK 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv64xxx_i2c_hw_init (struct mv64xxx_i2c_data*) ; 

__attribute__((used)) static void
mv64xxx_i2c_fsm(struct mv64xxx_i2c_data *drv_data, u32 status)
{
	/*
	 * If state is idle, then this is likely the remnants of an old
	 * operation that driver has given up on or the user has killed.
	 * If so, issue the stop condition and go to idle.
	 */
	if (drv_data->state == MV64XXX_I2C_STATE_IDLE) {
		drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
		return;
	}

	/* The status from the ctlr [mostly] tells us what to do next */
	switch (status) {
	/* Start condition interrupt */
	case MV64XXX_I2C_STATUS_MAST_START: /* 0x08 */
	case MV64XXX_I2C_STATUS_MAST_REPEAT_START: /* 0x10 */
		drv_data->action = MV64XXX_I2C_ACTION_SEND_ADDR_1;
		drv_data->state = MV64XXX_I2C_STATE_WAITING_FOR_ADDR_1_ACK;
		break;

	/* Performing a write */
	case MV64XXX_I2C_STATUS_MAST_WR_ADDR_ACK: /* 0x18 */
		if (drv_data->msg->flags & I2C_M_TEN) {
			drv_data->action = MV64XXX_I2C_ACTION_SEND_ADDR_2;
			drv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOR_ADDR_2_ACK;
			break;
		}
		/* FALLTHRU */
	case MV64XXX_I2C_STATUS_MAST_WR_ADDR_2_ACK: /* 0xd0 */
	case MV64XXX_I2C_STATUS_MAST_WR_ACK: /* 0x28 */
		if ((drv_data->bytes_left == 0)
				|| (drv_data->aborting
					&& (drv_data->byte_posn != 0))) {
			if (drv_data->send_stop || drv_data->aborting) {
				drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
				drv_data->state = MV64XXX_I2C_STATE_IDLE;
			} else {
				drv_data->action =
					MV64XXX_I2C_ACTION_SEND_RESTART;
				drv_data->state =
					MV64XXX_I2C_STATE_WAITING_FOR_RESTART;
			}
		} else {
			drv_data->action = MV64XXX_I2C_ACTION_SEND_DATA;
			drv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_ACK;
			drv_data->bytes_left--;
		}
		break;

	/* Performing a read */
	case MV64XXX_I2C_STATUS_MAST_RD_ADDR_ACK: /* 40 */
		if (drv_data->msg->flags & I2C_M_TEN) {
			drv_data->action = MV64XXX_I2C_ACTION_SEND_ADDR_2;
			drv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOR_ADDR_2_ACK;
			break;
		}
		/* FALLTHRU */
	case MV64XXX_I2C_STATUS_MAST_RD_ADDR_2_ACK: /* 0xe0 */
		if (drv_data->bytes_left == 0) {
			drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
			drv_data->state = MV64XXX_I2C_STATE_IDLE;
			break;
		}
		/* FALLTHRU */
	case MV64XXX_I2C_STATUS_MAST_RD_DATA_ACK: /* 0x50 */
		if (status != MV64XXX_I2C_STATUS_MAST_RD_DATA_ACK)
			drv_data->action = MV64XXX_I2C_ACTION_CONTINUE;
		else {
			drv_data->action = MV64XXX_I2C_ACTION_RCV_DATA;
			drv_data->bytes_left--;
		}
		drv_data->state = MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_DATA;

		if ((drv_data->bytes_left == 1) || drv_data->aborting)
			drv_data->cntl_bits &= ~MV64XXX_I2C_REG_CONTROL_ACK;
		break;

	case MV64XXX_I2C_STATUS_MAST_RD_DATA_NO_ACK: /* 0x58 */
		drv_data->action = MV64XXX_I2C_ACTION_RCV_DATA_STOP;
		drv_data->state = MV64XXX_I2C_STATE_IDLE;
		break;

	case MV64XXX_I2C_STATUS_MAST_WR_ADDR_NO_ACK: /* 0x20 */
	case MV64XXX_I2C_STATUS_MAST_WR_NO_ACK: /* 30 */
	case MV64XXX_I2C_STATUS_MAST_RD_ADDR_NO_ACK: /* 48 */
		/* Doesn't seem to be a device at other end */
		drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
		drv_data->state = MV64XXX_I2C_STATE_IDLE;
		drv_data->rc = -ENXIO;
		break;

	default:
		dev_err(&drv_data->adapter.dev,
			"mv64xxx_i2c_fsm: Ctlr Error -- state: 0x%x, "
			"status: 0x%x, addr: 0x%x, flags: 0x%x\n",
			 drv_data->state, status, drv_data->msg->addr,
			 drv_data->msg->flags);
		drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
		mv64xxx_i2c_hw_init(drv_data);
		drv_data->rc = -EIO;
	}
}