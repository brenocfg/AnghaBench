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
struct dss_module_power {int num_clk; struct dss_clk* clk_config; } ;
struct dss_clk {int /*<<< orphan*/  clk_name; } ;
struct dpu_kms {struct dss_module_power mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct dss_clk *_dpu_kms_get_clk(struct dpu_kms *dpu_kms,
		char *clock_name)
{
	struct dss_module_power *mp = &dpu_kms->mp;
	int i;

	for (i = 0; i < mp->num_clk; i++) {
		if (!strcmp(mp->clk_config[i].clk_name, clock_name))
			return &mp->clk_config[i];
	}

	return NULL;
}