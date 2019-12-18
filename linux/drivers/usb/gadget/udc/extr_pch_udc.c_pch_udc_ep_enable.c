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
typedef  int u32 ;
struct usb_endpoint_descriptor {int bmAttributes; } ;
struct pch_udc_ep {int in; int num; int /*<<< orphan*/  dev; } ;
struct pch_udc_cfg_data {int cur_cfg; int cur_intf; int cur_alt; } ;

/* Variables and functions */
 int UDC_CSR_NE_ALT_SHIFT ; 
 int UDC_CSR_NE_CFG_SHIFT ; 
 int UDC_CSR_NE_DIR_SHIFT ; 
 int UDC_CSR_NE_INTF_SHIFT ; 
 int UDC_CSR_NE_MAX_PKT_SHIFT ; 
 int UDC_CSR_NE_NUM_SHIFT ; 
 int UDC_CSR_NE_TYPE_SHIFT ; 
 int UDC_EPIN_BUFF_SIZE ; 
 int /*<<< orphan*/  UDC_EPIN_IDX (int) ; 
 int UDC_EPOUT_BUFF_SIZE ; 
 int /*<<< orphan*/  UDC_EPOUT_IDX (int) ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int /*<<< orphan*/  pch_udc_ep_fifo_flush (struct pch_udc_ep*,int) ; 
 int /*<<< orphan*/  pch_udc_ep_set_bufsz (struct pch_udc_ep*,int,int) ; 
 int /*<<< orphan*/  pch_udc_ep_set_maxpkt (struct pch_udc_ep*,int) ; 
 int /*<<< orphan*/  pch_udc_ep_set_nak (struct pch_udc_ep*) ; 
 int /*<<< orphan*/  pch_udc_ep_set_trfr_type (struct pch_udc_ep*,int) ; 
 int /*<<< orphan*/  pch_udc_write_csr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int usb_endpoint_maxp (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static void pch_udc_ep_enable(struct pch_udc_ep *ep,
			       struct pch_udc_cfg_data *cfg,
			       const struct usb_endpoint_descriptor *desc)
{
	u32 val = 0;
	u32 buff_size = 0;

	pch_udc_ep_set_trfr_type(ep, desc->bmAttributes);
	if (ep->in)
		buff_size = UDC_EPIN_BUFF_SIZE;
	else
		buff_size = UDC_EPOUT_BUFF_SIZE;
	pch_udc_ep_set_bufsz(ep, buff_size, ep->in);
	pch_udc_ep_set_maxpkt(ep, usb_endpoint_maxp(desc));
	pch_udc_ep_set_nak(ep);
	pch_udc_ep_fifo_flush(ep, ep->in);
	/* Configure the endpoint */
	val = ep->num << UDC_CSR_NE_NUM_SHIFT | ep->in << UDC_CSR_NE_DIR_SHIFT |
	      ((desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) <<
		UDC_CSR_NE_TYPE_SHIFT) |
	      (cfg->cur_cfg << UDC_CSR_NE_CFG_SHIFT) |
	      (cfg->cur_intf << UDC_CSR_NE_INTF_SHIFT) |
	      (cfg->cur_alt << UDC_CSR_NE_ALT_SHIFT) |
	      usb_endpoint_maxp(desc) << UDC_CSR_NE_MAX_PKT_SHIFT;

	if (ep->in)
		pch_udc_write_csr(ep->dev, val, UDC_EPIN_IDX(ep->num));
	else
		pch_udc_write_csr(ep->dev, val, UDC_EPOUT_IDX(ep->num));
}