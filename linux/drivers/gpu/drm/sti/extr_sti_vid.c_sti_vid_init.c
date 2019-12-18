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
struct sti_vid {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ VID_ALP ; 
 int VID_ALP_OPAQUE ; 
 scalar_t__ VID_BC ; 
 int VID_BC_DFLT ; 
 scalar_t__ VID_CSAT ; 
 int VID_CSAT_DFLT ; 
 scalar_t__ VID_CTL ; 
 int VID_CTL_IGNORE ; 
 int VID_CTL_PSI_ENABLE ; 
 scalar_t__ VID_TINT ; 
 int VID_TINT_DFLT ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sti_vid_init(struct sti_vid *vid)
{
	/* Enable PSI, Mask layer */
	writel(VID_CTL_PSI_ENABLE | VID_CTL_IGNORE, vid->regs + VID_CTL);

	/* Opaque */
	writel(VID_ALP_OPAQUE, vid->regs + VID_ALP);

	/* Brightness, contrast, tint, saturation */
	writel(VID_BC_DFLT, vid->regs + VID_BC);
	writel(VID_TINT_DFLT, vid->regs + VID_TINT);
	writel(VID_CSAT_DFLT, vid->regs + VID_CSAT);
}