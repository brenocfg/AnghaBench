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
struct dwc3_gadget_ep_cmd_params {int /*<<< orphan*/  param0; } ;
struct dwc3_ep {int dummy; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DEPCMD_SETTRANSFRESOURCE ; 
 int /*<<< orphan*/  DWC3_DEPXFERCFG_NUM_XFER_RES (int) ; 
 int dwc3_send_gadget_ep_cmd (struct dwc3_ep*,int /*<<< orphan*/ ,struct dwc3_gadget_ep_cmd_params*) ; 
 int /*<<< orphan*/  memset (struct dwc3_gadget_ep_cmd_params*,int,int) ; 

__attribute__((used)) static int dwc3_gadget_set_xfer_resource(struct dwc3_ep *dep)
{
	struct dwc3_gadget_ep_cmd_params params;

	memset(&params, 0x00, sizeof(params));

	params.param0 = DWC3_DEPXFERCFG_NUM_XFER_RES(1);

	return dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_SETTRANSFRESOURCE,
			&params);
}