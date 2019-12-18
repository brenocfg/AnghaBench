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
struct cdns3 {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  cdns3_device_irq_handler ; 
 int /*<<< orphan*/  cdns3_device_thread_irq_handler ; 
 int /*<<< orphan*/  cdns3_drd_switch_gadget (struct cdns3*,int) ; 
 int /*<<< orphan*/  cdns3_gadget_exit (struct cdns3*) ; 
 int cdns3_gadget_start (struct cdns3*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cdns3*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __cdns3_gadget_init(struct cdns3 *cdns)
{
	int ret = 0;

	/* Ensure 32-bit DMA Mask in case we switched back from Host mode */
	ret = dma_set_mask_and_coherent(cdns->dev, DMA_BIT_MASK(32));
	if (ret) {
		dev_err(cdns->dev, "Failed to set dma mask: %d\n", ret);
		return ret;
	}

	cdns3_drd_switch_gadget(cdns, 1);
	pm_runtime_get_sync(cdns->dev);

	ret = cdns3_gadget_start(cdns);
	if (ret)
		return ret;

	/*
	 * Because interrupt line can be shared with other components in
	 * driver it can't use IRQF_ONESHOT flag here.
	 */
	ret = devm_request_threaded_irq(cdns->dev, cdns->dev_irq,
					cdns3_device_irq_handler,
					cdns3_device_thread_irq_handler,
					IRQF_SHARED, dev_name(cdns->dev), cdns);

	if (ret)
		goto err0;

	return 0;
err0:
	cdns3_gadget_exit(cdns);
	return ret;
}