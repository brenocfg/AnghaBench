#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct i2c_msg {int addr; } ;
struct bcm_iproc_i2c_dev {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  M_CMD_OFFSET ; 
#define  M_CMD_STATUS_FIFO_UNDERRUN 134 
#define  M_CMD_STATUS_LOST_ARB 133 
 int M_CMD_STATUS_MASK ; 
#define  M_CMD_STATUS_NACK_ADDR 132 
#define  M_CMD_STATUS_NACK_DATA 131 
#define  M_CMD_STATUS_RX_FIFO_FULL 130 
 int M_CMD_STATUS_SHIFT ; 
#define  M_CMD_STATUS_SUCCESS 129 
#define  M_CMD_STATUS_TIMEOUT 128 
 int /*<<< orphan*/  bcm_iproc_i2c_enable_disable (struct bcm_iproc_i2c_dev*,int) ; 
 int /*<<< orphan*/  bcm_iproc_i2c_init (struct bcm_iproc_i2c_dev*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int iproc_i2c_rd_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_iproc_i2c_check_status(struct bcm_iproc_i2c_dev *iproc_i2c,
				      struct i2c_msg *msg)
{
	u32 val;

	val = iproc_i2c_rd_reg(iproc_i2c, M_CMD_OFFSET);
	val = (val >> M_CMD_STATUS_SHIFT) & M_CMD_STATUS_MASK;

	switch (val) {
	case M_CMD_STATUS_SUCCESS:
		return 0;

	case M_CMD_STATUS_LOST_ARB:
		dev_dbg(iproc_i2c->device, "lost bus arbitration\n");
		return -EAGAIN;

	case M_CMD_STATUS_NACK_ADDR:
		dev_dbg(iproc_i2c->device, "NAK addr:0x%02x\n", msg->addr);
		return -ENXIO;

	case M_CMD_STATUS_NACK_DATA:
		dev_dbg(iproc_i2c->device, "NAK data\n");
		return -ENXIO;

	case M_CMD_STATUS_TIMEOUT:
		dev_dbg(iproc_i2c->device, "bus timeout\n");
		return -ETIMEDOUT;

	case M_CMD_STATUS_FIFO_UNDERRUN:
		dev_dbg(iproc_i2c->device, "FIFO under-run\n");
		return -ENXIO;

	case M_CMD_STATUS_RX_FIFO_FULL:
		dev_dbg(iproc_i2c->device, "RX FIFO full\n");
		return -ETIMEDOUT;

	default:
		dev_dbg(iproc_i2c->device, "unknown error code=%d\n", val);

		/* re-initialize i2c for recovery */
		bcm_iproc_i2c_enable_disable(iproc_i2c, false);
		bcm_iproc_i2c_init(iproc_i2c);
		bcm_iproc_i2c_enable_disable(iproc_i2c, true);

		return -EIO;
	}
}