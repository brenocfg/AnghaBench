#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  info; int /*<<< orphan*/  ncpus; } ;
struct TYPE_4__ {TYPE_1__ mc_physcpuinfo; } ;
struct xen_mc {TYPE_2__ u; int /*<<< orphan*/  cmd; } ;
struct mcinfo_logical_cpu {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HYPERVISOR_mca (struct xen_mc*) ; 
 int /*<<< orphan*/  VIRQ_MCA ; 
 int /*<<< orphan*/  XEN_MC_physcpuinfo ; 
 int bind_virq_to_irqhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_physinfo ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xen_mc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncpus ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_mce_interrupt ; 

__attribute__((used)) static int bind_virq_for_mce(void)
{
	int ret;
	struct xen_mc mc_op;

	memset(&mc_op, 0, sizeof(struct xen_mc));

	/* Fetch physical CPU Numbers */
	mc_op.cmd = XEN_MC_physcpuinfo;
	set_xen_guest_handle(mc_op.u.mc_physcpuinfo.info, g_physinfo);
	ret = HYPERVISOR_mca(&mc_op);
	if (ret) {
		pr_err("Failed to get CPU numbers\n");
		return ret;
	}

	/* Fetch each CPU Physical Info for later reference*/
	ncpus = mc_op.u.mc_physcpuinfo.ncpus;
	g_physinfo = kcalloc(ncpus, sizeof(struct mcinfo_logical_cpu),
			     GFP_KERNEL);
	if (!g_physinfo)
		return -ENOMEM;
	set_xen_guest_handle(mc_op.u.mc_physcpuinfo.info, g_physinfo);
	ret = HYPERVISOR_mca(&mc_op);
	if (ret) {
		pr_err("Failed to get CPU info\n");
		kfree(g_physinfo);
		return ret;
	}

	ret  = bind_virq_to_irqhandler(VIRQ_MCA, 0,
				       xen_mce_interrupt, 0, "mce", NULL);
	if (ret < 0) {
		pr_err("Failed to bind virq\n");
		kfree(g_physinfo);
		return ret;
	}

	return 0;
}