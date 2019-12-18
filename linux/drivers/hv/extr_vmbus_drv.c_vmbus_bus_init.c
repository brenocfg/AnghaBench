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
typedef  int u64 ;
struct TYPE_2__ {int misc_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ONLINE_DYN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HV_CRASH_CTL_CRASH_NOTIFY_MSG ; 
 int HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE ; 
 int /*<<< orphan*/  VMBUS_MESSAGE_SINT ; 
 int /*<<< orphan*/  atomic_notifier_chain_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuhp_remove_state (int) ; 
 int cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_bus ; 
 int /*<<< orphan*/ * hv_ctl_table_hdr ; 
 int /*<<< orphan*/  hv_get_crash_ctl (int) ; 
 int hv_init () ; 
 int /*<<< orphan*/  hv_kmsg_dumper ; 
 void* hv_panic_page ; 
 int /*<<< orphan*/  hv_remove_vmbus_irq () ; 
 int /*<<< orphan*/  hv_root_table ; 
 int /*<<< orphan*/  hv_setup_vmbus_irq (int /*<<< orphan*/ ) ; 
 int hv_stimer_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_stimer_free () ; 
 int hv_synic_alloc () ; 
 int /*<<< orphan*/  hv_synic_cleanup ; 
 int /*<<< orphan*/  hv_synic_free () ; 
 int /*<<< orphan*/  hv_synic_init ; 
 int hyperv_cpuhp_online ; 
 int /*<<< orphan*/  hyperv_die_block ; 
 int /*<<< orphan*/  hyperv_panic_block ; 
 int kmsg_dump_register (int /*<<< orphan*/ *) ; 
 TYPE_1__ ms_hyperv ; 
 int /*<<< orphan*/  panic_notifier_list ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  register_die_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * register_sysctl_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ *) ; 
 int vmbus_connect () ; 
 int /*<<< orphan*/  vmbus_isr ; 
 int /*<<< orphan*/  vmbus_request_offers () ; 

__attribute__((used)) static int vmbus_bus_init(void)
{
	int ret;

	/* Hypervisor initialization...setup hypercall page..etc */
	ret = hv_init();
	if (ret != 0) {
		pr_err("Unable to initialize the hypervisor - 0x%x\n", ret);
		return ret;
	}

	ret = bus_register(&hv_bus);
	if (ret)
		return ret;

	hv_setup_vmbus_irq(vmbus_isr);

	ret = hv_synic_alloc();
	if (ret)
		goto err_alloc;

	ret = hv_stimer_alloc(VMBUS_MESSAGE_SINT);
	if (ret < 0)
		goto err_alloc;

	/*
	 * Initialize the per-cpu interrupt state and stimer state.
	 * Then connect to the host.
	 */
	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "hyperv/vmbus:online",
				hv_synic_init, hv_synic_cleanup);
	if (ret < 0)
		goto err_cpuhp;
	hyperv_cpuhp_online = ret;

	ret = vmbus_connect();
	if (ret)
		goto err_connect;

	/*
	 * Only register if the crash MSRs are available
	 */
	if (ms_hyperv.misc_features & HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE) {
		u64 hyperv_crash_ctl;
		/*
		 * Sysctl registration is not fatal, since by default
		 * reporting is enabled.
		 */
		hv_ctl_table_hdr = register_sysctl_table(hv_root_table);
		if (!hv_ctl_table_hdr)
			pr_err("Hyper-V: sysctl table register error");

		/*
		 * Register for panic kmsg callback only if the right
		 * capability is supported by the hypervisor.
		 */
		hv_get_crash_ctl(hyperv_crash_ctl);
		if (hyperv_crash_ctl & HV_CRASH_CTL_CRASH_NOTIFY_MSG) {
			hv_panic_page = (void *)get_zeroed_page(GFP_KERNEL);
			if (hv_panic_page) {
				ret = kmsg_dump_register(&hv_kmsg_dumper);
				if (ret)
					pr_err("Hyper-V: kmsg dump register "
						"error 0x%x\n", ret);
			} else
				pr_err("Hyper-V: panic message page memory "
					"allocation failed");
		}

		register_die_notifier(&hyperv_die_block);
		atomic_notifier_chain_register(&panic_notifier_list,
					       &hyperv_panic_block);
	}

	vmbus_request_offers();

	return 0;

err_connect:
	cpuhp_remove_state(hyperv_cpuhp_online);
err_cpuhp:
	hv_stimer_free();
err_alloc:
	hv_synic_free();
	hv_remove_vmbus_irq();

	bus_unregister(&hv_bus);
	free_page((unsigned long)hv_panic_page);
	unregister_sysctl_table(hv_ctl_table_hdr);
	hv_ctl_table_hdr = NULL;
	return ret;
}