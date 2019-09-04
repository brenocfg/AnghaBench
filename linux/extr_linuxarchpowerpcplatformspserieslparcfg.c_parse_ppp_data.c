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
struct hvcall_ppp_data {unsigned long entitlement; unsigned long group_num; unsigned long active_system_procs; unsigned long pool_num; int active_procs_in_pool; unsigned long unallocated_weight; unsigned long weight; unsigned long capped; unsigned long unallocated_entitlement; unsigned long phys_platform_procs; unsigned long max_proc_cap_avail; unsigned long entitled_proc_cap_avail; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_lppaca () ; 
 int h_get_ppp (struct hvcall_ppp_data*) ; 
 int /*<<< orphan*/  h_pic (unsigned long*,unsigned long*) ; 
 scalar_t__ lppaca_shared_proc (int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long) ; 

__attribute__((used)) static void parse_ppp_data(struct seq_file *m)
{
	struct hvcall_ppp_data ppp_data;
	struct device_node *root;
	const __be32 *perf_level;
	int rc;

	rc = h_get_ppp(&ppp_data);
	if (rc)
		return;

	seq_printf(m, "partition_entitled_capacity=%lld\n",
	           ppp_data.entitlement);
	seq_printf(m, "group=%d\n", ppp_data.group_num);
	seq_printf(m, "system_active_processors=%d\n",
	           ppp_data.active_system_procs);

	/* pool related entries are appropriate for shared configs */
	if (lppaca_shared_proc(get_lppaca())) {
		unsigned long pool_idle_time, pool_procs;

		seq_printf(m, "pool=%d\n", ppp_data.pool_num);

		/* report pool_capacity in percentage */
		seq_printf(m, "pool_capacity=%d\n",
			   ppp_data.active_procs_in_pool * 100);

		h_pic(&pool_idle_time, &pool_procs);
		seq_printf(m, "pool_idle_time=%ld\n", pool_idle_time);
		seq_printf(m, "pool_num_procs=%ld\n", pool_procs);
	}

	seq_printf(m, "unallocated_capacity_weight=%d\n",
		   ppp_data.unallocated_weight);
	seq_printf(m, "capacity_weight=%d\n", ppp_data.weight);
	seq_printf(m, "capped=%d\n", ppp_data.capped);
	seq_printf(m, "unallocated_capacity=%lld\n",
		   ppp_data.unallocated_entitlement);

	/* The last bits of information returned from h_get_ppp are only
	 * valid if the ibm,partition-performance-parameters-level
	 * property is >= 1.
	 */
	root = of_find_node_by_path("/");
	if (root) {
		perf_level = of_get_property(root,
				"ibm,partition-performance-parameters-level",
					     NULL);
		if (perf_level && (be32_to_cpup(perf_level) >= 1)) {
			seq_printf(m,
			    "physical_procs_allocated_to_virtualization=%d\n",
				   ppp_data.phys_platform_procs);
			seq_printf(m, "max_proc_capacity_available=%d\n",
				   ppp_data.max_proc_cap_avail);
			seq_printf(m, "entitled_proc_capacity_available=%d\n",
				   ppp_data.entitled_proc_cap_avail);
		}

		of_node_put(root);
	}
}