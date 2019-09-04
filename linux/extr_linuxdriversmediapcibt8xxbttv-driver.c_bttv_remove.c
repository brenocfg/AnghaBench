#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_device {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_9__ {size_t nr; size_t type; int /*<<< orphan*/  v4l2_dev; TYPE_1__* pci; } ;
struct bttv {int shutdown; TYPE_5__ c; int /*<<< orphan*/  bt848_mmio; int /*<<< orphan*/  main; int /*<<< orphan*/  radio_ctrl_handler; int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_8__ {scalar_t__ has_dvb; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_GPIO_DMA_CTL ; 
 int /*<<< orphan*/  BT848_GPIO_OUT_EN ; 
 int /*<<< orphan*/  BT848_INT_MASK ; 
 int /*<<< orphan*/  BT848_INT_STAT ; 
 int /*<<< orphan*/  btand (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btcx_riscmem_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ bttv_gpio ; 
 int /*<<< orphan*/  bttv_gpio_tracking (struct bttv*,char*) ; 
 int /*<<< orphan*/  bttv_input_fini (struct bttv*) ; 
 int /*<<< orphan*/  bttv_sub_del_devices (TYPE_5__*) ; 
 TYPE_4__* bttv_tvcards ; 
 int /*<<< orphan*/  bttv_unregister_video (struct bttv*) ; 
 scalar_t__ bttv_verbose ; 
 int /*<<< orphan*/ ** bttvs ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fini_bttv_i2c (struct bttv*) ; 
 int /*<<< orphan*/  flush_request_modules (struct bttv*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bttv*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bttv*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 
 struct v4l2_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,size_t) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bttv* to_bttv (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bttv_remove(struct pci_dev *pci_dev)
{
	struct v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	struct bttv *btv = to_bttv(v4l2_dev);

	if (bttv_verbose)
		pr_info("%d: unloading\n", btv->c.nr);

	if (bttv_tvcards[btv->c.type].has_dvb)
		flush_request_modules(btv);

	/* shutdown everything (DMA+IRQs) */
	btand(~15, BT848_GPIO_DMA_CTL);
	btwrite(0, BT848_INT_MASK);
	btwrite(~0x0, BT848_INT_STAT);
	btwrite(0x0, BT848_GPIO_OUT_EN);
	if (bttv_gpio)
		bttv_gpio_tracking(btv,"cleanup");

	/* tell gpio modules we are leaving ... */
	btv->shutdown=1;
	bttv_input_fini(btv);
	bttv_sub_del_devices(&btv->c);

	/* unregister i2c_bus + input */
	fini_bttv_i2c(btv);

	/* unregister video4linux */
	bttv_unregister_video(btv);

	/* free allocated memory */
	v4l2_ctrl_handler_free(&btv->ctrl_handler);
	v4l2_ctrl_handler_free(&btv->radio_ctrl_handler);
	btcx_riscmem_free(btv->c.pci,&btv->main);

	/* free resources */
	free_irq(btv->c.pci->irq,btv);
	iounmap(btv->bt848_mmio);
	release_mem_region(pci_resource_start(btv->c.pci,0),
			   pci_resource_len(btv->c.pci,0));
	pci_disable_device(btv->c.pci);

	v4l2_device_unregister(&btv->c.v4l2_dev);
	bttvs[btv->c.nr] = NULL;
	kfree(btv);

	return;
}