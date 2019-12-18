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
typedef  int /*<<< orphan*/  u64 ;
struct dss_clk {int /*<<< orphan*/  clk; } ;
struct dpu_kms {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct dss_clk* _dpu_kms_get_clk (struct dpu_kms*,char*) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 

u64 dpu_kms_get_clk_rate(struct dpu_kms *dpu_kms, char *clock_name)
{
	struct dss_clk *clk;

	clk = _dpu_kms_get_clk(dpu_kms, clock_name);
	if (!clk)
		return -EINVAL;

	return clk_get_rate(clk->clk);
}