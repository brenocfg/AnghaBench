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
typedef  void* u32 ;
struct gbe_timing_info {int flags; int pll_m; int pll_n; scalar_t__ pll_p; } ;
struct TYPE_2__ {void* fp_vdrv; void* fp_hdrv; void* fp_de; void* vt_flags; } ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  FP_DE ; 
 int /*<<< orphan*/  FP_HDRV ; 
 int /*<<< orphan*/  FP_VDRV ; 
 int /*<<< orphan*/  HDRV_INVERT ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int /*<<< orphan*/  SET_GBE_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  VDRV_INVERT ; 
 int /*<<< orphan*/  VT_FLAGS ; 
 TYPE_1__* gbe ; 

__attribute__((used)) static void gbefb_setup_flatpanel(struct gbe_timing_info *timing)
{
	int fp_wid, fp_hgt, fp_vbs, fp_vbe;
	u32 outputVal = 0;

	SET_GBE_FIELD(VT_FLAGS, HDRV_INVERT, outputVal,
		(timing->flags & FB_SYNC_HOR_HIGH_ACT) ? 0 : 1);
	SET_GBE_FIELD(VT_FLAGS, VDRV_INVERT, outputVal,
		(timing->flags & FB_SYNC_VERT_HIGH_ACT) ? 0 : 1);
	gbe->vt_flags = outputVal;

	/* Turn on the flat panel */
	fp_wid = 1600;
	fp_hgt = 1024;
	fp_vbs = 0;
	fp_vbe = 1600;
	timing->pll_m = 4;
	timing->pll_n = 1;
	timing->pll_p = 0;

	outputVal = 0;
	SET_GBE_FIELD(FP_DE, ON, outputVal, fp_vbs);
	SET_GBE_FIELD(FP_DE, OFF, outputVal, fp_vbe);
	gbe->fp_de = outputVal;
	outputVal = 0;
	SET_GBE_FIELD(FP_HDRV, OFF, outputVal, fp_wid);
	gbe->fp_hdrv = outputVal;
	outputVal = 0;
	SET_GBE_FIELD(FP_VDRV, ON, outputVal, 1);
	SET_GBE_FIELD(FP_VDRV, OFF, outputVal, fp_hgt + 1);
	gbe->fp_vdrv = outputVal;
}