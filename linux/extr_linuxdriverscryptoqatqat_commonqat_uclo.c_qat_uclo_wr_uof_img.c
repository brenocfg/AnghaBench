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
struct icp_qat_uclo_objhandle {unsigned int uimage_num; TYPE_1__* ae_uimage; } ;
struct icp_qat_fw_loader_handle {struct icp_qat_uclo_objhandle* obj_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  img_ptr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ qat_uclo_init_globals (struct icp_qat_fw_loader_handle*) ; 
 scalar_t__ qat_uclo_init_ustore (struct icp_qat_fw_loader_handle*,TYPE_1__*) ; 
 int /*<<< orphan*/  qat_uclo_wr_uimage_page (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_uclo_wr_uof_img(struct icp_qat_fw_loader_handle *handle)
{
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	unsigned int i;

	if (qat_uclo_init_globals(handle))
		return -EINVAL;
	for (i = 0; i < obj_handle->uimage_num; i++) {
		if (!obj_handle->ae_uimage[i].img_ptr)
			return -EINVAL;
		if (qat_uclo_init_ustore(handle, &obj_handle->ae_uimage[i]))
			return -EINVAL;
		qat_uclo_wr_uimage_page(handle,
					obj_handle->ae_uimage[i].img_ptr);
	}
	return 0;
}