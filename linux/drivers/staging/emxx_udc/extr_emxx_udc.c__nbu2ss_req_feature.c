#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_2__ {int bRequestType; int wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct nbu2ss_udc {int /*<<< orphan*/  ep0_buf; TYPE_1__ ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int USB_DIR_IN ; 
 scalar_t__ USB_DIR_OUT ; 
 int USB_ENDPOINT_HALT ; 
#define  USB_RECIP_DEVICE 129 
#define  USB_RECIP_ENDPOINT 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  _nbu2ss_create_ep0_packet (struct nbu2ss_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nbu2ss_endpoint_toggle_reset (struct nbu2ss_udc*,scalar_t__) ; 
 int /*<<< orphan*/  _nbu2ss_set_endpoint_stall (struct nbu2ss_udc*,scalar_t__,int) ; 
 int _nbu2ss_set_feature_device (struct nbu2ss_udc*,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int _nbu2ss_req_feature(struct nbu2ss_udc *udc, bool bset)
{
	u8	recipient = (u8)(udc->ctrl.bRequestType & USB_RECIP_MASK);
	u8	direction = (u8)(udc->ctrl.bRequestType & USB_DIR_IN);
	u16	selector  = le16_to_cpu(udc->ctrl.wValue);
	u16	wIndex    = le16_to_cpu(udc->ctrl.wIndex);
	u8	ep_adrs;
	int	result = -EOPNOTSUPP;

	if ((udc->ctrl.wLength != 0x0000) ||
	    (direction != USB_DIR_OUT)) {
		return -EINVAL;
	}

	switch (recipient) {
	case USB_RECIP_DEVICE:
		if (bset)
			result =
			_nbu2ss_set_feature_device(udc, selector, wIndex);
		break;

	case USB_RECIP_ENDPOINT:
		if (0x0000 == (wIndex & 0xFF70)) {
			if (selector == USB_ENDPOINT_HALT) {
				ep_adrs = wIndex & 0xFF;
				if (!bset) {
					_nbu2ss_endpoint_toggle_reset(udc,
								      ep_adrs);
				}

				_nbu2ss_set_endpoint_stall(udc, ep_adrs, bset);

				result = 0;
			}
		}
		break;

	default:
		break;
	}

	if (result >= 0)
		_nbu2ss_create_ep0_packet(udc, udc->ep0_buf, 0);

	return result;
}