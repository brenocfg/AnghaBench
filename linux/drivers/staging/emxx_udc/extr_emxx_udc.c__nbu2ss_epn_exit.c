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
typedef  size_t u32 ;
struct nbu2ss_udc {scalar_t__ vbus_active; TYPE_2__* p_regs; } ;
struct nbu2ss_ep {int epnum; scalar_t__ direct; } ;
struct TYPE_4__ {TYPE_1__* EP_REGS; int /*<<< orphan*/  USB_INT_ENA; } ;
struct TYPE_3__ {int /*<<< orphan*/  EP_INT_ENA; int /*<<< orphan*/  EP_CONTROL; int /*<<< orphan*/  EP_PCKT_ADRS; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t EPN_AUTO ; 
 size_t EPN_BCLR ; 
 size_t EPN_DIR0 ; 
 size_t EPN_EN ; 
 size_t EPN_IN_EN ; 
 size_t EPN_IN_END_EN ; 
 size_t EPN_ONAK ; 
 size_t EPN_OUT_EN ; 
 size_t EPN_OUT_END_EN ; 
 scalar_t__ USB_DIR_OUT ; 
 int /*<<< orphan*/  _nbu2ss_bitclr (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  _nbu2ss_bitset (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _nbu2ss_epn_exit(struct nbu2ss_udc *udc, struct nbu2ss_ep *ep)
{
	u32		num;
	u32		data;

	if ((ep->epnum == 0) || (udc->vbus_active == 0))
		return	-EINVAL;

	num = ep->epnum - 1;

	/*-------------------------------------------------------------*/
	/* RAM Transfer Address */
	_nbu2ss_writel(&udc->p_regs->EP_REGS[num].EP_PCKT_ADRS, 0);

	/*-------------------------------------------------------------*/
	/* Interrupt Disable */
	data = 1 << (ep->epnum + 8);
	_nbu2ss_bitclr(&udc->p_regs->USB_INT_ENA, data);

	if (ep->direct == USB_DIR_OUT) {
		/*---------------------------------------------------------*/
		/* OUT */
		data = EPN_ONAK | EPN_BCLR;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_EN | EPN_DIR0;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_OUT_EN | EPN_OUT_END_EN;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_INT_ENA, data);
	} else {
		/*---------------------------------------------------------*/
		/* IN */
		data = EPN_BCLR;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_EN | EPN_AUTO;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_IN_EN | EPN_IN_END_EN;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_INT_ENA, data);
	}

	return 0;
}