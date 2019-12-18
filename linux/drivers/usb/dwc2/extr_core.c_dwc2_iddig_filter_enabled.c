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
typedef  scalar_t__ u32 ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 scalar_t__ DWC2_CORE_REV_3_10a ; 
 int /*<<< orphan*/  GHWCFG4 ; 
 scalar_t__ GHWCFG4_IDDIG_FILT_EN ; 
 int /*<<< orphan*/  GOTGCTL ; 
 scalar_t__ GOTGCTL_DBNCE_FLTR_BYPASS ; 
 int /*<<< orphan*/  GSNPSID ; 
 int /*<<< orphan*/  dwc2_hw_is_otg (struct dwc2_hsotg*) ; 
 scalar_t__ dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dwc2_iddig_filter_enabled(struct dwc2_hsotg *hsotg)
{
	u32 gsnpsid;
	u32 ghwcfg4;

	if (!dwc2_hw_is_otg(hsotg))
		return false;

	/* Check if core configuration includes the IDDIG filter. */
	ghwcfg4 = dwc2_readl(hsotg, GHWCFG4);
	if (!(ghwcfg4 & GHWCFG4_IDDIG_FILT_EN))
		return false;

	/*
	 * Check if the IDDIG debounce filter is bypassed. Available
	 * in core version >= 3.10a.
	 */
	gsnpsid = dwc2_readl(hsotg, GSNPSID);
	if (gsnpsid >= DWC2_CORE_REV_3_10a) {
		u32 gotgctl = dwc2_readl(hsotg, GOTGCTL);

		if (gotgctl & GOTGCTL_DBNCE_FLTR_BYPASS)
			return false;
	}

	return true;
}