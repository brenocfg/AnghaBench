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
struct meson_gx_pwrc_vpu {int /*<<< orphan*/  vpu_clk; int /*<<< orphan*/  vapb_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_gx_pwrc_vpu_setup_clk(struct meson_gx_pwrc_vpu *pd)
{
	int ret;

	ret = clk_prepare_enable(pd->vpu_clk);
	if (ret)
		return ret;

	ret = clk_prepare_enable(pd->vapb_clk);
	if (ret)
		clk_disable_unprepare(pd->vpu_clk);

	return ret;
}