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
struct zx_vou_hw {scalar_t__ osd; scalar_t__ otfppu; scalar_t__ timing; scalar_t__ vouctl; } ;

/* Variables and functions */
 scalar_t__ OSD_INT_CLRSTA ; 
 int OSD_INT_ENABLE ; 
 scalar_t__ OSD_INT_MSK ; 
 scalar_t__ OSD_RST_CLR ; 
 scalar_t__ OTFPPU_RSZ_DATA_SOURCE ; 
 int /*<<< orphan*/  RST_PER_FRAME ; 
 scalar_t__ TIMING_INT_CTRL ; 
 int TIMING_INT_ENABLE ; 
 scalar_t__ TIMING_INT_STATE ; 
 scalar_t__ VOU_CLK_EN ; 
 scalar_t__ VOU_SOFT_RST ; 
 int /*<<< orphan*/  vou_dtrc_init (struct zx_vou_hw*) ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,int) ; 
 int /*<<< orphan*/  zx_writel_mask (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vou_hw_init(struct zx_vou_hw *vou)
{
	/* Release reset for all VOU modules */
	zx_writel(vou->vouctl + VOU_SOFT_RST, ~0);

	/* Enable all VOU module clocks */
	zx_writel(vou->vouctl + VOU_CLK_EN, ~0);

	/* Clear both OSD and TIMING_CTRL interrupt state */
	zx_writel(vou->osd + OSD_INT_CLRSTA, ~0);
	zx_writel(vou->timing + TIMING_INT_STATE, ~0);

	/* Enable OSD and TIMING_CTRL interrrupts */
	zx_writel(vou->osd + OSD_INT_MSK, OSD_INT_ENABLE);
	zx_writel(vou->timing + TIMING_INT_CTRL, TIMING_INT_ENABLE);

	/* Select GPC as input to gl/vl scaler as a sane default setting */
	zx_writel(vou->otfppu + OTFPPU_RSZ_DATA_SOURCE, 0x2a);

	/*
	 * Needs to reset channel and layer logic per frame when frame starts
	 * to get VOU work properly.
	 */
	zx_writel_mask(vou->osd + OSD_RST_CLR, RST_PER_FRAME, RST_PER_FRAME);

	vou_dtrc_init(vou);
}