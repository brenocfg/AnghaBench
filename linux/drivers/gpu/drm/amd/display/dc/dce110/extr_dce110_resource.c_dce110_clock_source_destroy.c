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
struct dce110_clk_src {struct dce110_clk_src* dvi_ss_params; struct dce110_clk_src* hdmi_ss_params; struct dce110_clk_src* dp_ss_params; } ;
struct clock_source {int dummy; } ;

/* Variables and functions */
 struct dce110_clk_src* TO_DCE110_CLK_SRC (struct clock_source*) ; 
 int /*<<< orphan*/  kfree (struct dce110_clk_src*) ; 

void dce110_clock_source_destroy(struct clock_source **clk_src)
{
	struct dce110_clk_src *dce110_clk_src;

	if (!clk_src)
		return;

	dce110_clk_src = TO_DCE110_CLK_SRC(*clk_src);

	kfree(dce110_clk_src->dp_ss_params);
	kfree(dce110_clk_src->hdmi_ss_params);
	kfree(dce110_clk_src->dvi_ss_params);

	kfree(dce110_clk_src);
	*clk_src = NULL;
}