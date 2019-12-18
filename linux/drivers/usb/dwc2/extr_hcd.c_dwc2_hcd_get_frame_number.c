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
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFNUM ; 
 int HFNUM_FRNUM_MASK ; 
 int HFNUM_FRNUM_SHIFT ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

int dwc2_hcd_get_frame_number(struct dwc2_hsotg *hsotg)
{
	u32 hfnum = dwc2_readl(hsotg, HFNUM);

#ifdef DWC2_DEBUG_SOF
	dev_vdbg(hsotg->dev, "DWC OTG HCD GET FRAME NUMBER %d\n",
		 (hfnum & HFNUM_FRNUM_MASK) >> HFNUM_FRNUM_SHIFT);
#endif
	return (hfnum & HFNUM_FRNUM_MASK) >> HFNUM_FRNUM_SHIFT;
}