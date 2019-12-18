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
struct ishtp_device {int /*<<< orphan*/  devc; } ;

/* Variables and functions */
 int EBUSY ; 
 int IPC_ISH_IN_DMA ; 
 int /*<<< orphan*/  IPC_REG_ISH_RMP2 ; 
 unsigned int MAX_DMA_DELAY ; 
 int _ish_read_fw_sts_reg (struct ishtp_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ish_reg_write (struct ishtp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

int ish_disable_dma(struct ishtp_device *dev)
{
	unsigned int	dma_delay;

	/* Clear the dma enable bit */
	ish_reg_write(dev, IPC_REG_ISH_RMP2, 0);

	/* wait for dma inactive */
	for (dma_delay = 0; dma_delay < MAX_DMA_DELAY &&
		_ish_read_fw_sts_reg(dev) & (IPC_ISH_IN_DMA);
		dma_delay += 5)
		mdelay(5);

	if (dma_delay >= MAX_DMA_DELAY) {
		dev_err(dev->devc,
			"Wait for DMA inactive timeout\n");
		return	-EBUSY;
	}

	return 0;
}