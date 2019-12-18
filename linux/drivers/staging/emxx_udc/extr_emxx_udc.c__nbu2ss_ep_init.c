#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nbu2ss_udc {TYPE_3__* p_regs; } ;
struct TYPE_4__ {int maxpacket; } ;
struct nbu2ss_ep {int epnum; int ep_type; int direct; TYPE_1__ ep; } ;
struct TYPE_6__ {TYPE_2__* EP_REGS; int /*<<< orphan*/  USB_INT_ENA; } ;
struct TYPE_5__ {int /*<<< orphan*/  EP_INT_ENA; int /*<<< orphan*/  EP_CONTROL; int /*<<< orphan*/  EP_PCKT_ADRS; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPN_AUTO ; 
 int EPN_BCLR ; 
 int EPN_BUF_SINGLE ; 
 int EPN_BULK ; 
 int EPN_DIR0 ; 
 int EPN_EN ; 
 int EPN_INTERRUPT ; 
 int EPN_IN_EN ; 
 int EPN_IN_END_EN ; 
 int EPN_ISO ; 
 int EPN_ISTL ; 
 int EPN_ONAK ; 
 int EPN_OSTL ; 
 int EPN_OSTL_EN ; 
 int EPN_OUT_EN ; 
 int EPN_OUT_END_EN ; 
 int USB_DIR_OUT ; 
#define  USB_ENDPOINT_XFER_BULK 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int /*<<< orphan*/  _nbu2ss_bitclr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _nbu2ss_bitset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _nbu2ss_endpoint_toggle_reset (struct nbu2ss_udc*,int) ; 
 int _nbu2ss_get_begin_ram_address (struct nbu2ss_udc*) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int _nbu2ss_ep_init(struct nbu2ss_udc *udc, struct nbu2ss_ep *ep)
{
	u32		num;
	u32		data;
	u32		begin_adrs;

	if (ep->epnum == 0)
		return	-EINVAL;

	num = ep->epnum - 1;

	/*-------------------------------------------------------------*/
	/* RAM Transfer Address */
	begin_adrs = _nbu2ss_get_begin_ram_address(udc);
	data = (begin_adrs << 16) | ep->ep.maxpacket;
	_nbu2ss_writel(&udc->p_regs->EP_REGS[num].EP_PCKT_ADRS, data);

	/*-------------------------------------------------------------*/
	/* Interrupt Enable */
	data = 1 << (ep->epnum + 8);
	_nbu2ss_bitset(&udc->p_regs->USB_INT_ENA, data);

	/*-------------------------------------------------------------*/
	/* Endpoint Type(Mode) */
	/*   Bulk, Interrupt, ISO */
	switch (ep->ep_type) {
	case USB_ENDPOINT_XFER_BULK:
		data = EPN_BULK;
		break;

	case USB_ENDPOINT_XFER_INT:
		data = EPN_BUF_SINGLE | EPN_INTERRUPT;
		break;

	case USB_ENDPOINT_XFER_ISOC:
		data = EPN_ISO;
		break;

	default:
		data = 0;
		break;
	}

	_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);
	_nbu2ss_endpoint_toggle_reset(udc, (ep->epnum | ep->direct));

	if (ep->direct == USB_DIR_OUT) {
		/*---------------------------------------------------------*/
		/* OUT */
		data = EPN_EN | EPN_BCLR | EPN_DIR0;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_ONAK | EPN_OSTL_EN | EPN_OSTL;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_OUT_EN | EPN_OUT_END_EN;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_INT_ENA, data);
	} else {
		/*---------------------------------------------------------*/
		/* IN */
		data = EPN_EN | EPN_BCLR | EPN_AUTO;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_ISTL;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_IN_EN | EPN_IN_END_EN;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_INT_ENA, data);
	}

	return 0;
}