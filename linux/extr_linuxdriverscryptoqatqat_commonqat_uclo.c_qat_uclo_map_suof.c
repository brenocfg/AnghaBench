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
struct icp_qat_suof_img_hdr {int ae_mask; } ;
struct TYPE_2__ {unsigned int num_simgs; struct icp_qat_suof_img_hdr* simg_hdr; } ;
struct icp_qat_suof_handle {TYPE_1__ img_table; } ;
struct icp_qat_suof_filehdr {unsigned int num_chunks; } ;
struct icp_qat_suof_chunk_hdr {int dummy; } ;
struct icp_qat_fw_loader_handle {struct icp_qat_suof_handle* sobj_handle; } ;
typedef  int /*<<< orphan*/  img_header ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICP_QAT_UCLO_MAX_AE ; 
 struct icp_qat_suof_img_hdr* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int qat_uclo_check_simg_compat (struct icp_qat_fw_loader_handle*,struct icp_qat_suof_img_hdr*) ; 
 scalar_t__ qat_uclo_check_suof_format (struct icp_qat_suof_filehdr*) ; 
 int /*<<< orphan*/  qat_uclo_map_simg (struct icp_qat_suof_handle*,struct icp_qat_suof_img_hdr*,struct icp_qat_suof_chunk_hdr*) ; 
 int qat_uclo_map_suof_file_hdr (struct icp_qat_fw_loader_handle*,struct icp_qat_suof_filehdr*,int) ; 
 int /*<<< orphan*/  qat_uclo_map_suof_symobjs (struct icp_qat_suof_handle*,struct icp_qat_suof_chunk_hdr*) ; 
 int /*<<< orphan*/  qat_uclo_tail_img (struct icp_qat_suof_img_hdr*,int,unsigned int) ; 

__attribute__((used)) static int qat_uclo_map_suof(struct icp_qat_fw_loader_handle *handle,
			     struct icp_qat_suof_filehdr *suof_ptr,
			     int suof_size)
{
	struct icp_qat_suof_handle *suof_handle = handle->sobj_handle;
	struct icp_qat_suof_chunk_hdr *suof_chunk_hdr = NULL;
	struct icp_qat_suof_img_hdr *suof_img_hdr = NULL;
	int ret = 0, ae0_img = ICP_QAT_UCLO_MAX_AE;
	unsigned int i = 0;
	struct icp_qat_suof_img_hdr img_header;

	if (!suof_ptr || (suof_size == 0)) {
		pr_err("QAT: input parameter SUOF pointer/size is NULL\n");
		return -EINVAL;
	}
	if (qat_uclo_check_suof_format(suof_ptr))
		return -EINVAL;
	ret = qat_uclo_map_suof_file_hdr(handle, suof_ptr, suof_size);
	if (ret)
		return ret;
	suof_chunk_hdr = (struct icp_qat_suof_chunk_hdr *)
			 ((uintptr_t)suof_ptr + sizeof(*suof_ptr));

	qat_uclo_map_suof_symobjs(suof_handle, suof_chunk_hdr);
	suof_handle->img_table.num_simgs = suof_ptr->num_chunks - 1;

	if (suof_handle->img_table.num_simgs != 0) {
		suof_img_hdr = kcalloc(suof_handle->img_table.num_simgs,
				       sizeof(img_header),
				       GFP_KERNEL);
		if (!suof_img_hdr)
			return -ENOMEM;
		suof_handle->img_table.simg_hdr = suof_img_hdr;
	}

	for (i = 0; i < suof_handle->img_table.num_simgs; i++) {
		qat_uclo_map_simg(handle->sobj_handle, &suof_img_hdr[i],
				  &suof_chunk_hdr[1 + i]);
		ret = qat_uclo_check_simg_compat(handle,
						 &suof_img_hdr[i]);
		if (ret)
			return ret;
		if ((suof_img_hdr[i].ae_mask & 0x1) != 0)
			ae0_img = i;
	}
	qat_uclo_tail_img(suof_img_hdr, ae0_img,
			  suof_handle->img_table.num_simgs);
	return 0;
}