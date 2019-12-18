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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3_ep {int /*<<< orphan*/  resource_index; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DEPCMD ; 
 int /*<<< orphan*/  DWC3_DEPCMD_GET_RSC_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dwc3_gadget_ep_get_transfer_index(struct dwc3_ep *dep)
{
	u32			res_id;

	res_id = dwc3_readl(dep->regs, DWC3_DEPCMD);
	dep->resource_index = DWC3_DEPCMD_GET_RSC_IDX(res_id);
}