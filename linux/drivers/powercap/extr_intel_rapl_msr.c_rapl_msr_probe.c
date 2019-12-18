#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {int pcap_rapl_online; int /*<<< orphan*/  control_type; int /*<<< orphan*/  write_raw; int /*<<< orphan*/  read_raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ONLINE_DYN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powercap_register_control_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powercap_unregister_control_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rapl_add_platform_domain (TYPE_1__*) ; 
 int /*<<< orphan*/  rapl_cpu_down_prep ; 
 int /*<<< orphan*/  rapl_cpu_online ; 
 TYPE_1__ rapl_msr_priv ; 
 int /*<<< orphan*/  rapl_msr_read_raw ; 
 int /*<<< orphan*/  rapl_msr_write_raw ; 

__attribute__((used)) static int rapl_msr_probe(struct platform_device *pdev)
{
	int ret;

	rapl_msr_priv.read_raw = rapl_msr_read_raw;
	rapl_msr_priv.write_raw = rapl_msr_write_raw;

	rapl_msr_priv.control_type = powercap_register_control_type(NULL, "intel-rapl", NULL);
	if (IS_ERR(rapl_msr_priv.control_type)) {
		pr_debug("failed to register powercap control_type.\n");
		return PTR_ERR(rapl_msr_priv.control_type);
	}

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "powercap/rapl:online",
				rapl_cpu_online, rapl_cpu_down_prep);
	if (ret < 0)
		goto out;
	rapl_msr_priv.pcap_rapl_online = ret;

	/* Don't bail out if PSys is not supported */
	rapl_add_platform_domain(&rapl_msr_priv);

	return 0;

out:
	if (ret)
		powercap_unregister_control_type(rapl_msr_priv.control_type);
	return ret;
}