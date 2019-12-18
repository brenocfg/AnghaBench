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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_SLEEP_STATE ; 
 scalar_t__ PMU_KEYLARGO_BASED ; 
 int /*<<< orphan*/  option_lid_wakeup ; 
 int /*<<< orphan*/  option_server_mode ; 
 scalar_t__ pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pmu_kind ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmu_options_proc_show(struct seq_file *m, void *v)
{
#if defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
	if (pmu_kind == PMU_KEYLARGO_BASED &&
	    pmac_call_feature(PMAC_FTR_SLEEP_STATE,NULL,0,-1) >= 0)
		seq_printf(m, "lid_wakeup=%d\n", option_lid_wakeup);
#endif
	if (pmu_kind == PMU_KEYLARGO_BASED)
		seq_printf(m, "server_mode=%d\n", option_server_mode);

	return 0;
}