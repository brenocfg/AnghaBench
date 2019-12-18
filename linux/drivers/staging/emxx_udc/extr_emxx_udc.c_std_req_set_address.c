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
struct TYPE_4__ {int bRequestType; int wIndex; int wLength; int /*<<< orphan*/  wValue; } ;
struct nbu2ss_udc {int /*<<< orphan*/  ep0_buf; TYPE_1__* p_regs; TYPE_2__ ctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/  USB_ADDRESS; } ;

/* Variables and functions */
 int EINVAL ; 
 int USB_ADRS_SHIFT ; 
 int /*<<< orphan*/  _nbu2ss_create_ep0_packet (struct nbu2ss_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int std_req_set_address(struct nbu2ss_udc *udc)
{
	int		result = 0;
	u32		wValue = le16_to_cpu(udc->ctrl.wValue);

	if ((udc->ctrl.bRequestType != 0x00)	||
	    (udc->ctrl.wIndex != 0x0000)	||
		(udc->ctrl.wLength != 0x0000)) {
		return -EINVAL;
	}

	if (wValue != (wValue & 0x007F))
		return -EINVAL;

	wValue <<= USB_ADRS_SHIFT;

	_nbu2ss_writel(&udc->p_regs->USB_ADDRESS, wValue);
	_nbu2ss_create_ep0_packet(udc, udc->ep0_buf, 0);

	return result;
}