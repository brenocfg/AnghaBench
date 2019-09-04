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
struct pmu {int dummy; } ;
struct hws_qsi_info_block {int /*<<< orphan*/  dear; int /*<<< orphan*/  tear; scalar_t__ es; } ;
struct hws_lsctl_request_block {int /*<<< orphan*/  dear; int /*<<< orphan*/  tear; scalar_t__ cd; scalar_t__ cs; } ;
struct cpu_hw_sf {int flags; struct hws_lsctl_request_block lsctl; } ;

/* Variables and functions */
 int PMU_F_ENABLED ; 
 int PMU_F_ERR_MASK ; 
 int /*<<< orphan*/  cpu_hw_sf ; 
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,int) ; 
 int lsctl (struct hws_lsctl_request_block*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  qsi (struct hws_qsi_info_block*) ; 
 int /*<<< orphan*/  sfdbg ; 
 struct cpu_hw_sf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumsf_pmu_disable(struct pmu *pmu)
{
	struct cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);
	struct hws_lsctl_request_block inactive;
	struct hws_qsi_info_block si;
	int err;

	if (!(cpuhw->flags & PMU_F_ENABLED))
		return;

	if (cpuhw->flags & PMU_F_ERR_MASK)
		return;

	/* Switch off sampling activation control */
	inactive = cpuhw->lsctl;
	inactive.cs = 0;
	inactive.cd = 0;

	err = lsctl(&inactive);
	if (err) {
		pr_err("Loading sampling controls failed: op=%i err=%i\n",
			2, err);
		return;
	}

	/* Save state of TEAR and DEAR register contents */
	if (!qsi(&si)) {
		/* TEAR/DEAR values are valid only if the sampling facility is
		 * enabled.  Note that cpumsf_pmu_disable() might be called even
		 * for a disabled sampling facility because cpumsf_pmu_enable()
		 * controls the enable/disable state.
		 */
		if (si.es) {
			cpuhw->lsctl.tear = si.tear;
			cpuhw->lsctl.dear = si.dear;
		}
	} else
		debug_sprintf_event(sfdbg, 3, "cpumsf_pmu_disable: "
				    "qsi() failed with err=%i\n", err);

	cpuhw->flags &= ~PMU_F_ENABLED;
}