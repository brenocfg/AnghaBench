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
struct mxsfb_drm_private {scalar_t__ clk_axi; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 

void mxsfb_enable_axi_clk(struct mxsfb_drm_private *mxsfb)
{
	if (mxsfb->clk_axi)
		clk_prepare_enable(mxsfb->clk_axi);
}