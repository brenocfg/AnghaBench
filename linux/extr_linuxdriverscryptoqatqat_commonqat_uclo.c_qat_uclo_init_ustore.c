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
typedef  int /*<<< orphan*/  uint64_t ;
struct icp_qat_uof_image {int /*<<< orphan*/  ae_assigned; int /*<<< orphan*/  fill_pattern; } ;
struct icp_qat_uclo_objhandle {TYPE_2__* ae_data; } ;
struct icp_qat_uclo_encapme {struct icp_qat_uclo_encap_page* page; struct icp_qat_uof_image* img_ptr; } ;
struct icp_qat_uclo_encap_page {unsigned int beg_addr_p; unsigned int micro_words_num; } ;
struct icp_qat_fw_loader_handle {TYPE_1__* hal_handle; struct icp_qat_uclo_objhandle* obj_handle; } ;
struct TYPE_4__ {unsigned int eff_ustore_size; } ;
struct TYPE_3__ {unsigned char ae_max_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int ICP_QAT_UCLO_MAX_USTORE ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qat_hal_wr_uwords (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (unsigned char,unsigned long*) ; 

__attribute__((used)) static int qat_uclo_init_ustore(struct icp_qat_fw_loader_handle *handle,
				struct icp_qat_uclo_encapme *image)
{
	unsigned int i;
	struct icp_qat_uclo_encap_page *page;
	struct icp_qat_uof_image *uof_image;
	unsigned char ae;
	unsigned int ustore_size;
	unsigned int patt_pos;
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	uint64_t *fill_data;

	uof_image = image->img_ptr;
	fill_data = kcalloc(ICP_QAT_UCLO_MAX_USTORE, sizeof(uint64_t),
			    GFP_KERNEL);
	if (!fill_data)
		return -ENOMEM;
	for (i = 0; i < ICP_QAT_UCLO_MAX_USTORE; i++)
		memcpy(&fill_data[i], &uof_image->fill_pattern,
		       sizeof(uint64_t));
	page = image->page;

	for (ae = 0; ae < handle->hal_handle->ae_max_num; ae++) {
		if (!test_bit(ae, (unsigned long *)&uof_image->ae_assigned))
			continue;
		ustore_size = obj_handle->ae_data[ae].eff_ustore_size;
		patt_pos = page->beg_addr_p + page->micro_words_num;

		qat_hal_wr_uwords(handle, (unsigned char)ae, 0,
				  page->beg_addr_p, &fill_data[0]);
		qat_hal_wr_uwords(handle, (unsigned char)ae, patt_pos,
				  ustore_size - patt_pos + 1,
				  &fill_data[page->beg_addr_p]);
	}
	kfree(fill_data);
	return 0;
}