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
struct TYPE_4__ {int max_speed; int speed; char* name; int sg_supported; int quirk_avoids_skb_reserve; int /*<<< orphan*/  ep_list; int /*<<< orphan*/ * ops; } ;
struct cdns3_device {int onchip_buffers; int /*<<< orphan*/  setup_dma; int /*<<< orphan*/  setup_buf; int /*<<< orphan*/  sysdev; void* zlp_buf; int /*<<< orphan*/  dev; TYPE_2__ gadget; void* dev_ver; TYPE_1__* regs; int /*<<< orphan*/  aligned_buf_list; int /*<<< orphan*/  aligned_buf_wq; int /*<<< orphan*/  pending_status_wq; int /*<<< orphan*/  lock; } ;
struct cdns3 {struct cdns3_device* gadget_dev; int /*<<< orphan*/  dev; TYPE_1__* dev_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_cap2; int /*<<< orphan*/  usb_cap1; int /*<<< orphan*/  usb_cap6; } ;

/* Variables and functions */
 int CDNS3_EP_ZLP_BUF_SIZE ; 
 int ENOMEM ; 
 void* GET_DEV_BASE_VERSION (void*) ; 
 int /*<<< orphan*/  GFP_DMA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int USB_CAP2_ACTUAL_MEM_SIZE (int) ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_SUPER 129 
#define  USB_SPEED_UNKNOWN 128 
 int /*<<< orphan*/  cdns3_free_aligned_request_buf ; 
 int /*<<< orphan*/  cdns3_free_all_eps (struct cdns3_device*) ; 
 int /*<<< orphan*/  cdns3_gadget_ops ; 
 int cdns3_init_eps (struct cdns3_device*) ; 
 int /*<<< orphan*/  cdns3_pending_setup_status_handler ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_property_read_u16 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int usb_add_gadget_udc (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int usb_get_maximum_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns3_gadget_start(struct cdns3 *cdns)
{
	struct cdns3_device *priv_dev;
	u32 max_speed;
	int ret;

	priv_dev = kzalloc(sizeof(*priv_dev), GFP_KERNEL);
	if (!priv_dev)
		return -ENOMEM;

	cdns->gadget_dev = priv_dev;
	priv_dev->sysdev = cdns->dev;
	priv_dev->dev = cdns->dev;
	priv_dev->regs = cdns->dev_regs;

	device_property_read_u16(priv_dev->dev, "cdns,on-chip-buff-size",
				 &priv_dev->onchip_buffers);

	if (priv_dev->onchip_buffers <=  0) {
		u32 reg = readl(&priv_dev->regs->usb_cap2);

		priv_dev->onchip_buffers = USB_CAP2_ACTUAL_MEM_SIZE(reg);
	}

	if (!priv_dev->onchip_buffers)
		priv_dev->onchip_buffers = 256;

	max_speed = usb_get_maximum_speed(cdns->dev);

	/* Check the maximum_speed parameter */
	switch (max_speed) {
	case USB_SPEED_FULL:
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPER:
		break;
	default:
		dev_err(cdns->dev, "invalid maximum_speed parameter %d\n",
			max_speed);
		/* fall through */
	case USB_SPEED_UNKNOWN:
		/* default to superspeed */
		max_speed = USB_SPEED_SUPER;
		break;
	}

	/* fill gadget fields */
	priv_dev->gadget.max_speed = max_speed;
	priv_dev->gadget.speed = USB_SPEED_UNKNOWN;
	priv_dev->gadget.ops = &cdns3_gadget_ops;
	priv_dev->gadget.name = "usb-ss-gadget";
	priv_dev->gadget.sg_supported = 1;
	priv_dev->gadget.quirk_avoids_skb_reserve = 1;

	spin_lock_init(&priv_dev->lock);
	INIT_WORK(&priv_dev->pending_status_wq,
		  cdns3_pending_setup_status_handler);

	INIT_WORK(&priv_dev->aligned_buf_wq,
		  cdns3_free_aligned_request_buf);

	/* initialize endpoint container */
	INIT_LIST_HEAD(&priv_dev->gadget.ep_list);
	INIT_LIST_HEAD(&priv_dev->aligned_buf_list);

	ret = cdns3_init_eps(priv_dev);
	if (ret) {
		dev_err(priv_dev->dev, "Failed to create endpoints\n");
		goto err1;
	}

	/* allocate memory for setup packet buffer */
	priv_dev->setup_buf = dma_alloc_coherent(priv_dev->sysdev, 8,
						 &priv_dev->setup_dma, GFP_DMA);
	if (!priv_dev->setup_buf) {
		ret = -ENOMEM;
		goto err2;
	}

	priv_dev->dev_ver = readl(&priv_dev->regs->usb_cap6);

	dev_dbg(priv_dev->dev, "Device Controller version: %08x\n",
		readl(&priv_dev->regs->usb_cap6));
	dev_dbg(priv_dev->dev, "USB Capabilities:: %08x\n",
		readl(&priv_dev->regs->usb_cap1));
	dev_dbg(priv_dev->dev, "On-Chip memory configuration: %08x\n",
		readl(&priv_dev->regs->usb_cap2));

	priv_dev->dev_ver = GET_DEV_BASE_VERSION(priv_dev->dev_ver);

	priv_dev->zlp_buf = kzalloc(CDNS3_EP_ZLP_BUF_SIZE, GFP_KERNEL);
	if (!priv_dev->zlp_buf) {
		ret = -ENOMEM;
		goto err3;
	}

	/* add USB gadget device */
	ret = usb_add_gadget_udc(priv_dev->dev, &priv_dev->gadget);
	if (ret < 0) {
		dev_err(priv_dev->dev,
			"Failed to register USB device controller\n");
		goto err4;
	}

	return 0;
err4:
	kfree(priv_dev->zlp_buf);
err3:
	dma_free_coherent(priv_dev->sysdev, 8, priv_dev->setup_buf,
			  priv_dev->setup_dma);
err2:
	cdns3_free_all_eps(priv_dev);
err1:
	cdns->gadget_dev = NULL;
	return ret;
}