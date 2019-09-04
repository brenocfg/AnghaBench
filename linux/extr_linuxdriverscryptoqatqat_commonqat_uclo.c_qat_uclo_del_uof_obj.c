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
struct icp_qat_uclo_objhandle {unsigned int uimage_num; struct icp_qat_uclo_objhandle* obj_buf; struct icp_qat_uclo_objhandle* obj_hdr; int /*<<< orphan*/ * ae_data; TYPE_1__* ae_uimage; struct icp_qat_uclo_objhandle* uword_buf; } ;
struct icp_qat_fw_loader_handle {struct icp_qat_uclo_objhandle* obj_handle; TYPE_2__* hal_handle; scalar_t__ sobj_handle; } ;
struct TYPE_4__ {unsigned int ae_max_num; } ;
struct TYPE_3__ {struct icp_qat_uclo_objhandle* page; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct icp_qat_uclo_objhandle*) ; 
 int /*<<< orphan*/  qat_uclo_del_suof (struct icp_qat_fw_loader_handle*) ; 
 int /*<<< orphan*/  qat_uclo_free_ae_data (int /*<<< orphan*/ *) ; 

void qat_uclo_del_uof_obj(struct icp_qat_fw_loader_handle *handle)
{
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	unsigned int a;

	if (handle->sobj_handle)
		qat_uclo_del_suof(handle);
	if (!obj_handle)
		return;

	kfree(obj_handle->uword_buf);
	for (a = 0; a < obj_handle->uimage_num; a++)
		kfree(obj_handle->ae_uimage[a].page);

	for (a = 0; a < handle->hal_handle->ae_max_num; a++)
		qat_uclo_free_ae_data(&obj_handle->ae_data[a]);

	kfree(obj_handle->obj_hdr);
	kfree(obj_handle->obj_buf);
	kfree(obj_handle);
	handle->obj_handle = NULL;
}