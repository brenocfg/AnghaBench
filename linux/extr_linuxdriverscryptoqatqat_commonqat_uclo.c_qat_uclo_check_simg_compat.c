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
struct icp_qat_suof_img_hdr {scalar_t__ css_simg; } ;
struct icp_qat_simg_ae_mode {unsigned int dev_type; unsigned int devmax_ver; unsigned int devmin_ver; } ;
struct icp_qat_fw_loader_handle {TYPE_1__* hal_handle; } ;
struct TYPE_2__ {unsigned int revision_id; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PID_MAJOR_REV ; 
 unsigned int PID_MINOR_REV ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 unsigned int qat_uclo_get_dev_type (struct icp_qat_fw_loader_handle*) ; 

__attribute__((used)) static int qat_uclo_check_simg_compat(struct icp_qat_fw_loader_handle *handle,
				      struct icp_qat_suof_img_hdr *img_hdr)
{
	struct icp_qat_simg_ae_mode *img_ae_mode = NULL;
	unsigned int prod_rev, maj_ver, prod_type;

	prod_type = qat_uclo_get_dev_type(handle);
	img_ae_mode = (struct icp_qat_simg_ae_mode *)img_hdr->css_simg;
	prod_rev = PID_MAJOR_REV |
			 (PID_MINOR_REV & handle->hal_handle->revision_id);
	if (img_ae_mode->dev_type != prod_type) {
		pr_err("QAT: incompatible product type %x\n",
		       img_ae_mode->dev_type);
		return -EINVAL;
	}
	maj_ver = prod_rev & 0xff;
	if ((maj_ver > img_ae_mode->devmax_ver) ||
	    (maj_ver < img_ae_mode->devmin_ver)) {
		pr_err("QAT: incompatible device majver 0x%x\n", maj_ver);
		return -EINVAL;
	}
	return 0;
}