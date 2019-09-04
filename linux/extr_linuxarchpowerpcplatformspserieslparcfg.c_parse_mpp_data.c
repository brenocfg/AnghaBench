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
struct hvcall_mpp_data {int entitled_mem; int mapped_mem; int group_num; int pool_num; int mem_weight; int unallocated_mem_weight; int unallocated_entitlement; int pool_size; int loan_request; int backing_mem; } ;

/* Variables and functions */
 int h_get_mpp (struct hvcall_mpp_data*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static void parse_mpp_data(struct seq_file *m)
{
	struct hvcall_mpp_data mpp_data;
	int rc;

	rc = h_get_mpp(&mpp_data);
	if (rc)
		return;

	seq_printf(m, "entitled_memory=%ld\n", mpp_data.entitled_mem);

	if (mpp_data.mapped_mem != -1)
		seq_printf(m, "mapped_entitled_memory=%ld\n",
		           mpp_data.mapped_mem);

	seq_printf(m, "entitled_memory_group_number=%d\n", mpp_data.group_num);
	seq_printf(m, "entitled_memory_pool_number=%d\n", mpp_data.pool_num);

	seq_printf(m, "entitled_memory_weight=%d\n", mpp_data.mem_weight);
	seq_printf(m, "unallocated_entitled_memory_weight=%d\n",
	           mpp_data.unallocated_mem_weight);
	seq_printf(m, "unallocated_io_mapping_entitlement=%ld\n",
	           mpp_data.unallocated_entitlement);

	if (mpp_data.pool_size != -1)
		seq_printf(m, "entitled_memory_pool_size=%ld bytes\n",
		           mpp_data.pool_size);

	seq_printf(m, "entitled_memory_loan_request=%ld\n",
	           mpp_data.loan_request);

	seq_printf(m, "backing_memory=%ld bytes\n", mpp_data.backing_mem);
}