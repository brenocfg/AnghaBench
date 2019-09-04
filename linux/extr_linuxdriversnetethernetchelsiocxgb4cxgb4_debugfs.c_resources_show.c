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
struct seq_file {struct adapter* private; } ;
struct pf_resources {int /*<<< orphan*/  wx_caps; int /*<<< orphan*/  r_caps; int /*<<< orphan*/  nexactf; int /*<<< orphan*/  pmask; int /*<<< orphan*/  tc; int /*<<< orphan*/  niq; int /*<<< orphan*/  niqflint; int /*<<< orphan*/  nethctrl; int /*<<< orphan*/  neq; int /*<<< orphan*/  nvi; } ;
struct TYPE_2__ {struct pf_resources pfres; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resources_show(struct seq_file *seq, void *v)
{
	struct adapter *adapter = seq->private;
	struct pf_resources *pfres = &adapter->params.pfres;

	#define S(desc, fmt, var) \
		seq_printf(seq, "%-60s " fmt "\n", \
			   desc " (" #var "):", pfres->var)

	S("Virtual Interfaces", "%d", nvi);
	S("Egress Queues", "%d", neq);
	S("Ethernet Control", "%d", nethctrl);
	S("Ingress Queues/w Free Lists/Interrupts", "%d", niqflint);
	S("Ingress Queues", "%d", niq);
	S("Traffic Class", "%d", tc);
	S("Port Access Rights Mask", "%#x", pmask);
	S("MAC Address Filters", "%d", nexactf);
	S("Firmware Command Read Capabilities", "%#x", r_caps);
	S("Firmware Command Write/Execute Capabilities", "%#x", wx_caps);

	#undef S

	return 0;
}