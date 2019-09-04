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
struct icp_qat_uof_initmem {int dummy; } ;
struct icp_qat_uof_encap_obj {scalar_t__ beg_uof; int /*<<< orphan*/  obj_hdr; } ;
struct icp_qat_uof_chunkhdr {scalar_t__ offset; } ;
struct icp_qat_uclo_init_mem_table {struct icp_qat_uof_initmem* init_mem; int /*<<< orphan*/  entry_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICP_QAT_UOF_IMEM ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct icp_qat_uof_chunkhdr* qat_uclo_find_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qat_uclo_map_initmem_table(struct icp_qat_uof_encap_obj *encap_uof_obj,
			   struct icp_qat_uclo_init_mem_table *init_mem_tab)
{
	struct icp_qat_uof_chunkhdr *chunk_hdr;

	chunk_hdr = qat_uclo_find_chunk(encap_uof_obj->obj_hdr,
					ICP_QAT_UOF_IMEM, NULL);
	if (chunk_hdr) {
		memmove(&init_mem_tab->entry_num, encap_uof_obj->beg_uof +
			chunk_hdr->offset, sizeof(unsigned int));
		init_mem_tab->init_mem = (struct icp_qat_uof_initmem *)
		(encap_uof_obj->beg_uof + chunk_hdr->offset +
		sizeof(unsigned int));
	}
}