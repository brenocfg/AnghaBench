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
struct icp_qat_uclo_objhandle {int /*<<< orphan*/ * uword_buf; TYPE_2__* ae_uimage; } ;
struct icp_qat_uclo_encap_page {unsigned int beg_addr_p; unsigned int micro_words_num; } ;
struct icp_qat_fw_loader_handle {struct icp_qat_uclo_objhandle* obj_handle; } ;
struct TYPE_4__ {TYPE_1__* img_ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  fill_pattern; } ;

/* Variables and functions */
 unsigned int UWORD_CPYBUF_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qat_hal_wr_uwords (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qat_uclo_fill_uwords (struct icp_qat_uclo_objhandle*,struct icp_qat_uclo_encap_page*,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qat_uclo_wr_uimage_raw_page(struct icp_qat_fw_loader_handle *handle,
					struct icp_qat_uclo_encap_page
					*encap_page, unsigned int ae)
{
	unsigned int uw_physical_addr, uw_relative_addr, i, words_num, cpylen;
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	uint64_t fill_pat;

	/* load the page starting at appropriate ustore address */
	/* get fill-pattern from an image -- they are all the same */
	memcpy(&fill_pat, obj_handle->ae_uimage[0].img_ptr->fill_pattern,
	       sizeof(uint64_t));
	uw_physical_addr = encap_page->beg_addr_p;
	uw_relative_addr = 0;
	words_num = encap_page->micro_words_num;
	while (words_num) {
		if (words_num < UWORD_CPYBUF_SIZE)
			cpylen = words_num;
		else
			cpylen = UWORD_CPYBUF_SIZE;

		/* load the buffer */
		for (i = 0; i < cpylen; i++)
			qat_uclo_fill_uwords(obj_handle, encap_page,
					     &obj_handle->uword_buf[i],
					     uw_physical_addr + i,
					     uw_relative_addr + i, fill_pat);

		/* copy the buffer to ustore */
		qat_hal_wr_uwords(handle, (unsigned char)ae,
				  uw_physical_addr, cpylen,
				  obj_handle->uword_buf);

		uw_physical_addr += cpylen;
		uw_relative_addr += cpylen;
		words_num -= cpylen;
	}
}