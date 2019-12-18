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
typedef  int /*<<< orphan*/  u32 ;
struct usb_endpoint_descriptor {int dummy; } ;
struct dwc3_trb {void* param1; void* param0; int /*<<< orphan*/  ctrl; void* bph; void* bpl; } ;
struct dwc3_gadget_ep_cmd_params {void* param1; void* param0; int /*<<< orphan*/  ctrl; void* bph; void* bpl; } ;
struct TYPE_2__ {struct usb_endpoint_descriptor* desc; } ;
struct dwc3_ep {int flags; struct dwc3_trb* trb_pool; int /*<<< orphan*/  stream_capable; scalar_t__ trb_enqueue; scalar_t__ trb_dequeue; int /*<<< orphan*/  number; int /*<<< orphan*/  type; struct dwc3* dwc; TYPE_1__ endpoint; } ;
struct dwc3 {int /*<<< orphan*/  regs; } ;
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DALEPENA ; 
 int /*<<< orphan*/  DWC3_DALEPENA_EP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_DEPCMD_STARTTRANSFER ; 
 int DWC3_EP_ENABLED ; 
 int /*<<< orphan*/  DWC3_TRBCTL_LINK_TRB ; 
 int /*<<< orphan*/  DWC3_TRB_CTRL_HWO ; 
 int DWC3_TRB_NUM ; 
 int dwc3_gadget_set_ep_config (struct dwc3_ep*,unsigned int) ; 
 int dwc3_gadget_start_config (struct dwc3_ep*) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dwc3_send_gadget_ep_cmd (struct dwc3_ep*,int /*<<< orphan*/ ,struct dwc3_trb*) ; 
 int /*<<< orphan*/  dwc3_trb_dma_offset (struct dwc3_ep*,struct dwc3_trb*) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dwc3_trb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_dwc3_gadget_ep_enable (struct dwc3_ep*) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_type (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_xfer_bulk (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_xfer_control (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_xfer_int (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static int __dwc3_gadget_ep_enable(struct dwc3_ep *dep, unsigned int action)
{
	const struct usb_endpoint_descriptor *desc = dep->endpoint.desc;
	struct dwc3		*dwc = dep->dwc;

	u32			reg;
	int			ret;

	if (!(dep->flags & DWC3_EP_ENABLED)) {
		ret = dwc3_gadget_start_config(dep);
		if (ret)
			return ret;
	}

	ret = dwc3_gadget_set_ep_config(dep, action);
	if (ret)
		return ret;

	if (!(dep->flags & DWC3_EP_ENABLED)) {
		struct dwc3_trb	*trb_st_hw;
		struct dwc3_trb	*trb_link;

		dep->type = usb_endpoint_type(desc);
		dep->flags |= DWC3_EP_ENABLED;

		reg = dwc3_readl(dwc->regs, DWC3_DALEPENA);
		reg |= DWC3_DALEPENA_EP(dep->number);
		dwc3_writel(dwc->regs, DWC3_DALEPENA, reg);

		if (usb_endpoint_xfer_control(desc))
			goto out;

		/* Initialize the TRB ring */
		dep->trb_dequeue = 0;
		dep->trb_enqueue = 0;
		memset(dep->trb_pool, 0,
		       sizeof(struct dwc3_trb) * DWC3_TRB_NUM);

		/* Link TRB. The HWO bit is never reset */
		trb_st_hw = &dep->trb_pool[0];

		trb_link = &dep->trb_pool[DWC3_TRB_NUM - 1];
		trb_link->bpl = lower_32_bits(dwc3_trb_dma_offset(dep, trb_st_hw));
		trb_link->bph = upper_32_bits(dwc3_trb_dma_offset(dep, trb_st_hw));
		trb_link->ctrl |= DWC3_TRBCTL_LINK_TRB;
		trb_link->ctrl |= DWC3_TRB_CTRL_HWO;
	}

	/*
	 * Issue StartTransfer here with no-op TRB so we can always rely on No
	 * Response Update Transfer command.
	 */
	if ((usb_endpoint_xfer_bulk(desc) && !dep->stream_capable) ||
			usb_endpoint_xfer_int(desc)) {
		struct dwc3_gadget_ep_cmd_params params;
		struct dwc3_trb	*trb;
		dma_addr_t trb_dma;
		u32 cmd;

		memset(&params, 0, sizeof(params));
		trb = &dep->trb_pool[0];
		trb_dma = dwc3_trb_dma_offset(dep, trb);

		params.param0 = upper_32_bits(trb_dma);
		params.param1 = lower_32_bits(trb_dma);

		cmd = DWC3_DEPCMD_STARTTRANSFER;

		ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
		if (ret < 0)
			return ret;
	}

out:
	trace_dwc3_gadget_ep_enable(dep);

	return 0;
}