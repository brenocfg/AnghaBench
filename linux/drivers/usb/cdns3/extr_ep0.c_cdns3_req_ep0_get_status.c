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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wIndex; } ;
struct cdns3_endpoint {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;
struct cdns3_device {int /*<<< orphan*/  setup_dma; scalar_t__ setup_buf; TYPE_2__* regs; struct cdns3_endpoint** eps; int /*<<< orphan*/  u2_allowed; int /*<<< orphan*/  u1_allowed; TYPE_1__ gadget; int /*<<< orphan*/  wake_up_flag; int /*<<< orphan*/  is_selfpowered; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int /*<<< orphan*/  ep_sts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EP_STALL_PENDING ; 
 int /*<<< orphan*/  EP_STS_STALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_DEVICE_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  USB_DEVICE_SELF_POWERED ; 
 int /*<<< orphan*/  USB_DEV_STAT_U1_ENABLED ; 
 int /*<<< orphan*/  USB_DEV_STAT_U2_ENABLED ; 
 int /*<<< orphan*/  USB_ENDPOINT_HALT ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int cdns3_ep0_delegate_req (struct cdns3_device*,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  cdns3_ep0_run_transfer (struct cdns3_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 size_t cdns3_ep_addr_to_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns3_select_ep (struct cdns3_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns3_req_ep0_get_status(struct cdns3_device *priv_dev,
				    struct usb_ctrlrequest *ctrl)
{
	struct cdns3_endpoint *priv_ep;
	__le16 *response_pkt;
	u16 usb_status = 0;
	u32 recip;
	u8 index;

	recip = ctrl->bRequestType & USB_RECIP_MASK;

	switch (recip) {
	case USB_RECIP_DEVICE:
		/* self powered */
		if (priv_dev->is_selfpowered)
			usb_status = BIT(USB_DEVICE_SELF_POWERED);

		if (priv_dev->wake_up_flag)
			usb_status |= BIT(USB_DEVICE_REMOTE_WAKEUP);

		if (priv_dev->gadget.speed != USB_SPEED_SUPER)
			break;

		if (priv_dev->u1_allowed)
			usb_status |= BIT(USB_DEV_STAT_U1_ENABLED);

		if (priv_dev->u2_allowed)
			usb_status |= BIT(USB_DEV_STAT_U2_ENABLED);

		break;
	case USB_RECIP_INTERFACE:
		return cdns3_ep0_delegate_req(priv_dev, ctrl);
	case USB_RECIP_ENDPOINT:
		index = cdns3_ep_addr_to_index(ctrl->wIndex);
		priv_ep = priv_dev->eps[index];

		/* check if endpoint is stalled or stall is pending */
		cdns3_select_ep(priv_dev, ctrl->wIndex);
		if (EP_STS_STALL(readl(&priv_dev->regs->ep_sts)) ||
		    (priv_ep->flags & EP_STALL_PENDING))
			usb_status =  BIT(USB_ENDPOINT_HALT);
		break;
	default:
		return -EINVAL;
	}

	response_pkt = (__le16 *)priv_dev->setup_buf;
	*response_pkt = cpu_to_le16(usb_status);

	cdns3_ep0_run_transfer(priv_dev, priv_dev->setup_dma,
			       sizeof(*response_pkt), 1, 0);
	return 0;
}