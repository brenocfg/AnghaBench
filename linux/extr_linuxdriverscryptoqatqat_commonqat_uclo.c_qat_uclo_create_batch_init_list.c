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
struct icp_qat_uof_memvar_attr {int /*<<< orphan*/  value; scalar_t__ offset_in_byte; } ;
struct icp_qat_uof_initmem {unsigned int val_attr_num; scalar_t__ addr; } ;
struct icp_qat_uof_batch_init {int size; unsigned int ae; struct icp_qat_uof_batch_init* next; int /*<<< orphan*/ * value; scalar_t__ addr; } ;
struct icp_qat_fw_loader_handle {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct icp_qat_uof_batch_init*) ; 
 struct icp_qat_uof_batch_init* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ qat_hal_get_ins_num () ; 

__attribute__((used)) static int qat_uclo_create_batch_init_list(struct icp_qat_fw_loader_handle
					   *handle, struct icp_qat_uof_initmem
					   *init_mem, unsigned int ae,
					   struct icp_qat_uof_batch_init
					   **init_tab_base)
{
	struct icp_qat_uof_batch_init *init_header, *tail;
	struct icp_qat_uof_batch_init *mem_init, *tail_old;
	struct icp_qat_uof_memvar_attr *mem_val_attr;
	unsigned int i, flag = 0;

	mem_val_attr =
		(struct icp_qat_uof_memvar_attr *)((uintptr_t)init_mem +
		sizeof(struct icp_qat_uof_initmem));

	init_header = *init_tab_base;
	if (!init_header) {
		init_header = kzalloc(sizeof(*init_header), GFP_KERNEL);
		if (!init_header)
			return -ENOMEM;
		init_header->size = 1;
		*init_tab_base = init_header;
		flag = 1;
	}
	tail_old = init_header;
	while (tail_old->next)
		tail_old = tail_old->next;
	tail = tail_old;
	for (i = 0; i < init_mem->val_attr_num; i++) {
		mem_init = kzalloc(sizeof(*mem_init), GFP_KERNEL);
		if (!mem_init)
			goto out_err;
		mem_init->ae = ae;
		mem_init->addr = init_mem->addr + mem_val_attr->offset_in_byte;
		mem_init->value = &mem_val_attr->value;
		mem_init->size = 4;
		mem_init->next = NULL;
		tail->next = mem_init;
		tail = mem_init;
		init_header->size += qat_hal_get_ins_num();
		mem_val_attr++;
	}
	return 0;
out_err:
	while (tail_old) {
		mem_init = tail_old->next;
		kfree(tail_old);
		tail_old = mem_init;
	}
	if (flag)
		kfree(*init_tab_base);
	return -ENOMEM;
}