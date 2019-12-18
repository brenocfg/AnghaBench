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
typedef  int uint32_t ;
struct i2c_msg {size_t len; int* buf; } ;
struct bcm_iproc_i2c_dev {size_t rx_bytes; struct i2c_msg* msg; } ;

/* Variables and functions */
 int M_RX_DATA_MASK ; 
 int M_RX_DATA_SHIFT ; 
 int /*<<< orphan*/  M_RX_OFFSET ; 
 int M_RX_STATUS_MASK ; 
 int M_RX_STATUS_SHIFT ; 
 int iproc_i2c_rd_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_iproc_i2c_read_valid_bytes(struct bcm_iproc_i2c_dev *iproc_i2c)
{
	struct i2c_msg *msg = iproc_i2c->msg;
	uint32_t val;

	/* Read valid data from RX FIFO */
	while (iproc_i2c->rx_bytes < msg->len) {
		val = iproc_i2c_rd_reg(iproc_i2c, M_RX_OFFSET);

		/* rx fifo empty */
		if (!((val >> M_RX_STATUS_SHIFT) & M_RX_STATUS_MASK))
			break;

		msg->buf[iproc_i2c->rx_bytes] =
			(val >> M_RX_DATA_SHIFT) & M_RX_DATA_MASK;
		iproc_i2c->rx_bytes++;
	}
}