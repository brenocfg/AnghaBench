#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct icp_qat_uof_initmem {int addr; int num_in_bytes; } ;
struct icp_qat_uclo_objhandle {unsigned int ustore_phy_size; TYPE_3__* ae_data; int /*<<< orphan*/ * umem_init_tab; } ;
struct icp_qat_fw_loader_handle {struct icp_qat_uclo_objhandle* obj_handle; } ;
struct TYPE_6__ {unsigned int slice_num; TYPE_2__* ae_slices; } ;
struct TYPE_5__ {TYPE_1__* encap_image; } ;
struct TYPE_4__ {unsigned int uwords_num; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ qat_uclo_create_batch_init_list (struct icp_qat_fw_loader_handle*,struct icp_qat_uof_initmem*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ qat_uclo_fetch_initmem_ae (struct icp_qat_fw_loader_handle*,struct icp_qat_uof_initmem*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int qat_uclo_init_umem_seg(struct icp_qat_fw_loader_handle *handle,
				  struct icp_qat_uof_initmem *init_mem)
{
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	unsigned int ae, ustore_size, uaddr, i;

	ustore_size = obj_handle->ustore_phy_size;
	if (qat_uclo_fetch_initmem_ae(handle, init_mem, ustore_size, &ae))
		return -EINVAL;
	if (qat_uclo_create_batch_init_list(handle, init_mem, ae,
					    &obj_handle->umem_init_tab[ae]))
		return -EINVAL;
	/* set the highest ustore address referenced */
	uaddr = (init_mem->addr + init_mem->num_in_bytes) >> 0x2;
	for (i = 0; i < obj_handle->ae_data[ae].slice_num; i++) {
		if (obj_handle->ae_data[ae].ae_slices[i].
		    encap_image->uwords_num < uaddr)
			obj_handle->ae_data[ae].ae_slices[i].
			encap_image->uwords_num = uaddr;
	}
	return 0;
}