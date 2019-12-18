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
struct nxp_fspi {int /*<<< orphan*/  clk_en; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nxp_fspi_clk_prep_enable(struct nxp_fspi *f)
{
	int ret;

	ret = clk_prepare_enable(f->clk_en);
	if (ret)
		return ret;

	ret = clk_prepare_enable(f->clk);
	if (ret) {
		clk_disable_unprepare(f->clk_en);
		return ret;
	}

	return 0;
}