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
struct TYPE_4__ {TYPE_1__* obj_hdr; } ;
struct icp_qat_uclo_objhandle {unsigned int prod_type; int prod_rev; TYPE_2__ encap_uof_obj; } ;
struct TYPE_3__ {unsigned int ac_dev_type; unsigned int max_cpu_ver; unsigned int min_cpu_ver; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,...) ; 

__attribute__((used)) static int qat_uclo_check_uof_compat(struct icp_qat_uclo_objhandle *obj_handle)
{
	unsigned int maj_ver, prod_type = obj_handle->prod_type;

	if (!(prod_type & obj_handle->encap_uof_obj.obj_hdr->ac_dev_type)) {
		pr_err("QAT: UOF type 0x%x doesn't match with platform 0x%x\n",
		       obj_handle->encap_uof_obj.obj_hdr->ac_dev_type,
		       prod_type);
		return -EINVAL;
	}
	maj_ver = obj_handle->prod_rev & 0xff;
	if ((obj_handle->encap_uof_obj.obj_hdr->max_cpu_ver < maj_ver) ||
	    (obj_handle->encap_uof_obj.obj_hdr->min_cpu_ver > maj_ver)) {
		pr_err("QAT: UOF majVer 0x%x out of range\n", maj_ver);
		return -EINVAL;
	}
	return 0;
}