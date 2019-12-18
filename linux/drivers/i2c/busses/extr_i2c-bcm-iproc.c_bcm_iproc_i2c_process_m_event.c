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
struct bcm_iproc_i2c_dev {int xfer_is_done; int /*<<< orphan*/  done; scalar_t__ irq; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_M_RX_THLD_SHIFT ; 
 int /*<<< orphan*/  IS_M_START_BUSY_SHIFT ; 
 int /*<<< orphan*/  IS_M_TX_UNDERRUN_SHIFT ; 
 int /*<<< orphan*/  bcm_iproc_i2c_read (struct bcm_iproc_i2c_dev*) ; 
 int /*<<< orphan*/  bcm_iproc_i2c_send (struct bcm_iproc_i2c_dev*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm_iproc_i2c_process_m_event(struct bcm_iproc_i2c_dev *iproc_i2c,
					  u32 status)
{
	/* TX FIFO is empty and we have more data to send */
	if (status & BIT(IS_M_TX_UNDERRUN_SHIFT))
		bcm_iproc_i2c_send(iproc_i2c);

	/* RX FIFO threshold is reached and data needs to be read out */
	if (status & BIT(IS_M_RX_THLD_SHIFT))
		bcm_iproc_i2c_read(iproc_i2c);

	/* transfer is done */
	if (status & BIT(IS_M_START_BUSY_SHIFT)) {
		iproc_i2c->xfer_is_done = 1;
		if (iproc_i2c->irq)
			complete(&iproc_i2c->done);
	}
}