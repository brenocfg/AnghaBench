#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  enum telemetry_unit { ____Placeholder_telemetry_unit } telemetry_unit ;
struct TYPE_2__ {int /*<<< orphan*/  telem_trace_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IOSS_TELEM_READ_WORD ; 
 int /*<<< orphan*/  IOSS_TELEM_TRACE_CTL_READ ; 
 int /*<<< orphan*/  IPC_PUNIT_BIOS_READ_TELE_TRACE_CTRL ; 
 int /*<<< orphan*/  PMC_IPC_PMC_TELEMTRY ; 
 int /*<<< orphan*/  TELEM_EXTRACT_VERBOSITY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TELEM_IOSS 129 
#define  TELEM_PSS 128 
 int intel_pmc_ipc_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int intel_punit_ipc_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 TYPE_1__* telm_conf ; 

__attribute__((used)) static int telemetry_plt_get_trace_verbosity(enum telemetry_unit telem_unit,
					     u32 *verbosity)
{
	u32 temp = 0;
	int ret;

	if (verbosity == NULL)
		return -EINVAL;

	mutex_lock(&(telm_conf->telem_trace_lock));
	switch (telem_unit) {
	case TELEM_PSS:
		ret = intel_punit_ipc_command(
				IPC_PUNIT_BIOS_READ_TELE_TRACE_CTRL,
				0, 0, NULL, &temp);
		if (ret) {
			pr_err("PSS TRACE_CTRL Read Failed\n");
			goto out;
		}

		break;

	case TELEM_IOSS:
		ret = intel_pmc_ipc_command(PMC_IPC_PMC_TELEMTRY,
				IOSS_TELEM_TRACE_CTL_READ, NULL, 0, &temp,
				IOSS_TELEM_READ_WORD);
		if (ret) {
			pr_err("IOSS TRACE_CTL Read Failed\n");
			goto out;
		}

		break;

	default:
		pr_err("Unknown Telemetry Unit Specified %d\n", telem_unit);
		ret = -EINVAL;
		break;
	}
	TELEM_EXTRACT_VERBOSITY(temp, *verbosity);

out:
	mutex_unlock(&(telm_conf->telem_trace_lock));
	return ret;
}