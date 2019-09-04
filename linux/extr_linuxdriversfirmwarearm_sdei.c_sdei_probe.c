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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ARM_SDEI_STARTING ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int SDEI_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ SDEI_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ SDEI_VERSION_VENDOR (int /*<<< orphan*/ ) ; 
 int cpu_pm_register_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_pm_unregister_notifier (int /*<<< orphan*/ *) ; 
 int cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int register_reboot_notifier (int /*<<< orphan*/ *) ; 
 int sdei_api_get_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdei_arch_get_entry_point (int) ; 
 int /*<<< orphan*/  sdei_cpuhp_down ; 
 int /*<<< orphan*/  sdei_cpuhp_up ; 
 int /*<<< orphan*/  sdei_entry_point ; 
 int /*<<< orphan*/  sdei_firmware_call ; 
 int sdei_get_conduit (struct platform_device*) ; 
 int /*<<< orphan*/  sdei_mark_interface_broken () ; 
 int sdei_platform_reset () ; 
 int /*<<< orphan*/  sdei_pm_nb ; 
 int /*<<< orphan*/  sdei_reboot_nb ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdei_probe(struct platform_device *pdev)
{
	int err;
	u64 ver = 0;
	int conduit;

	conduit = sdei_get_conduit(pdev);
	if (!sdei_firmware_call)
		return 0;

	err = sdei_api_get_version(&ver);
	if (err == -EOPNOTSUPP)
		pr_err("advertised but not implemented in platform firmware\n");
	if (err) {
		pr_err("Failed to get SDEI version: %d\n", err);
		sdei_mark_interface_broken();
		return err;
	}

	pr_info("SDEIv%d.%d (0x%x) detected in firmware.\n",
		(int)SDEI_VERSION_MAJOR(ver), (int)SDEI_VERSION_MINOR(ver),
		(int)SDEI_VERSION_VENDOR(ver));

	if (SDEI_VERSION_MAJOR(ver) != 1) {
		pr_warn("Conflicting SDEI version detected.\n");
		sdei_mark_interface_broken();
		return -EINVAL;
	}

	err = sdei_platform_reset();
	if (err)
		return err;

	sdei_entry_point = sdei_arch_get_entry_point(conduit);
	if (!sdei_entry_point) {
		/* Not supported due to hardware or boot configuration */
		sdei_mark_interface_broken();
		return 0;
	}

	err = cpu_pm_register_notifier(&sdei_pm_nb);
	if (err) {
		pr_warn("Failed to register CPU PM notifier...\n");
		goto error;
	}

	err = register_reboot_notifier(&sdei_reboot_nb);
	if (err) {
		pr_warn("Failed to register reboot notifier...\n");
		goto remove_cpupm;
	}

	err = cpuhp_setup_state(CPUHP_AP_ARM_SDEI_STARTING, "SDEI",
				&sdei_cpuhp_up, &sdei_cpuhp_down);
	if (err) {
		pr_warn("Failed to register CPU hotplug notifier...\n");
		goto remove_reboot;
	}

	return 0;

remove_reboot:
	unregister_reboot_notifier(&sdei_reboot_nb);

remove_cpupm:
	cpu_pm_unregister_notifier(&sdei_pm_nb);

error:
	sdei_mark_interface_broken();
	return err;
}