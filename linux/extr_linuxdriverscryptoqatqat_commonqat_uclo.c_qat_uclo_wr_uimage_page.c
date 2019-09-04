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
struct icp_qat_uof_image {int ctx_assigned; int /*<<< orphan*/  entry_address; int /*<<< orphan*/  ae_assigned; int /*<<< orphan*/  ae_mode; } ;
struct icp_qat_uclo_page {TYPE_4__* encap_page; } ;
struct icp_qat_uclo_objhandle {TYPE_3__* ae_data; } ;
struct icp_qat_fw_loader_handle {TYPE_1__* hal_handle; struct icp_qat_uclo_objhandle* obj_handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  def_page; } ;
struct TYPE_7__ {unsigned int slice_num; TYPE_2__* ae_slices; } ;
struct TYPE_6__ {int ctx_mask_assigned; struct icp_qat_uclo_page** cur_page; struct icp_qat_uclo_page* page; } ;
struct TYPE_5__ {unsigned char ae_max_num; } ;

/* Variables and functions */
 int ICP_QAT_CTX_MODE (int /*<<< orphan*/ ) ; 
 int ICP_QAT_UCLO_MAX_CTX ; 
 int /*<<< orphan*/  qat_hal_set_live_ctx (struct icp_qat_fw_loader_handle*,unsigned char,int) ; 
 int /*<<< orphan*/  qat_hal_set_pc (struct icp_qat_fw_loader_handle*,unsigned char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_uclo_wr_uimage_raw_page (struct icp_qat_fw_loader_handle*,TYPE_4__*,unsigned char) ; 
 int /*<<< orphan*/  test_bit (unsigned char,unsigned long*) ; 

__attribute__((used)) static void qat_uclo_wr_uimage_page(struct icp_qat_fw_loader_handle *handle,
				    struct icp_qat_uof_image *image)
{
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	unsigned int ctx_mask, s;
	struct icp_qat_uclo_page *page;
	unsigned char ae;
	int ctx;

	if (ICP_QAT_CTX_MODE(image->ae_mode) == ICP_QAT_UCLO_MAX_CTX)
		ctx_mask = 0xff;
	else
		ctx_mask = 0x55;
	/* load the default page and set assigned CTX PC
	 * to the entrypoint address */
	for (ae = 0; ae < handle->hal_handle->ae_max_num; ae++) {
		if (!test_bit(ae, (unsigned long *)&image->ae_assigned))
			continue;
		/* find the slice to which this image is assigned */
		for (s = 0; s < obj_handle->ae_data[ae].slice_num; s++) {
			if (image->ctx_assigned & obj_handle->ae_data[ae].
			    ae_slices[s].ctx_mask_assigned)
				break;
		}
		if (s >= obj_handle->ae_data[ae].slice_num)
			continue;
		page = obj_handle->ae_data[ae].ae_slices[s].page;
		if (!page->encap_page->def_page)
			continue;
		qat_uclo_wr_uimage_raw_page(handle, page->encap_page, ae);

		page = obj_handle->ae_data[ae].ae_slices[s].page;
		for (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++)
			obj_handle->ae_data[ae].ae_slices[s].cur_page[ctx] =
					(ctx_mask & (1 << ctx)) ? page : NULL;
		qat_hal_set_live_ctx(handle, (unsigned char)ae,
				     image->ctx_assigned);
		qat_hal_set_pc(handle, (unsigned char)ae, image->ctx_assigned,
			       image->entry_address);
	}
}