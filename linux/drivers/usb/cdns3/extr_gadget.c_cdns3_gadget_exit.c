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
struct cdns3_device {int size; struct cdns3_device* zlp_buf; int /*<<< orphan*/  setup_dma; int /*<<< orphan*/  setup_buf; int /*<<< orphan*/  sysdev; int /*<<< orphan*/  list; int /*<<< orphan*/  dma; int /*<<< orphan*/  buf; int /*<<< orphan*/  aligned_buf_list; int /*<<< orphan*/  gadget; } ;
struct cdns3_aligned_buf {int size; struct cdns3_aligned_buf* zlp_buf; int /*<<< orphan*/  setup_dma; int /*<<< orphan*/  setup_buf; int /*<<< orphan*/  sysdev; int /*<<< orphan*/  list; int /*<<< orphan*/  dma; int /*<<< orphan*/  buf; int /*<<< orphan*/  aligned_buf_list; int /*<<< orphan*/  gadget; } ;
struct cdns3 {struct cdns3_device* gadget_dev; int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns3_drd_switch_gadget (struct cdns3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns3_free_all_eps (struct cdns3_device*) ; 
 struct cdns3_device* cdns3_next_align_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cdns3*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cdns3_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

void cdns3_gadget_exit(struct cdns3 *cdns)
{
	struct cdns3_device *priv_dev;

	priv_dev = cdns->gadget_dev;

	devm_free_irq(cdns->dev, cdns->dev_irq, cdns);

	pm_runtime_mark_last_busy(cdns->dev);
	pm_runtime_put_autosuspend(cdns->dev);

	usb_del_gadget_udc(&priv_dev->gadget);

	cdns3_free_all_eps(priv_dev);

	while (!list_empty(&priv_dev->aligned_buf_list)) {
		struct cdns3_aligned_buf *buf;

		buf = cdns3_next_align_buf(&priv_dev->aligned_buf_list);
		dma_free_coherent(priv_dev->sysdev, buf->size,
				  buf->buf,
				  buf->dma);

		list_del(&buf->list);
		kfree(buf);
	}

	dma_free_coherent(priv_dev->sysdev, 8, priv_dev->setup_buf,
			  priv_dev->setup_dma);

	kfree(priv_dev->zlp_buf);
	kfree(priv_dev);
	cdns->gadget_dev = NULL;
	cdns3_drd_switch_gadget(cdns, 0);
}