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
struct TYPE_2__ {struct icp_qat_suof_handle* simg_hdr; } ;
struct icp_qat_suof_handle {TYPE_1__ img_table; } ;
struct icp_qat_fw_loader_handle {struct icp_qat_suof_handle* sobj_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct icp_qat_suof_handle*) ; 

__attribute__((used)) static void qat_uclo_del_suof(struct icp_qat_fw_loader_handle *handle)
{
	struct icp_qat_suof_handle *sobj_handle = handle->sobj_handle;

	kfree(sobj_handle->img_table.simg_hdr);
	sobj_handle->img_table.simg_hdr = NULL;
	kfree(handle->sobj_handle);
	handle->sobj_handle = NULL;
}