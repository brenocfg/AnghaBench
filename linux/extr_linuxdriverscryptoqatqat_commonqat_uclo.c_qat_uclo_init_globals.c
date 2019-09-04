#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ entry_num; } ;
struct icp_qat_uclo_objhandle {int global_inited; TYPE_4__* ae_data; TYPE_1__ init_mem_tab; } ;
struct icp_qat_fw_loader_handle {TYPE_2__* hal_handle; struct icp_qat_uclo_objhandle* obj_handle; } ;
struct TYPE_8__ {unsigned int slice_num; TYPE_3__* ae_slices; } ;
struct TYPE_7__ {int /*<<< orphan*/  encap_image; } ;
struct TYPE_6__ {unsigned int ae_max_num; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ qat_uclo_init_memory (struct icp_qat_fw_loader_handle*) ; 
 scalar_t__ qat_uclo_init_reg_sym (struct icp_qat_fw_loader_handle*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_uclo_init_globals(struct icp_qat_fw_loader_handle *handle)
{
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	unsigned int s, ae;

	if (obj_handle->global_inited)
		return 0;
	if (obj_handle->init_mem_tab.entry_num) {
		if (qat_uclo_init_memory(handle)) {
			pr_err("QAT: initialize memory failed\n");
			return -EINVAL;
		}
	}
	for (ae = 0; ae < handle->hal_handle->ae_max_num; ae++) {
		for (s = 0; s < obj_handle->ae_data[ae].slice_num; s++) {
			if (!obj_handle->ae_data[ae].ae_slices[s].encap_image)
				continue;
			if (qat_uclo_init_reg_sym(handle, ae,
						  obj_handle->ae_data[ae].
						  ae_slices[s].encap_image))
				return -EINVAL;
		}
	}
	obj_handle->global_inited = 1;
	return 0;
}