#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct icp_qat_uof_initmem {unsigned int addr; unsigned int num_in_bytes; scalar_t__ scope; int /*<<< orphan*/  sym_name; } ;
struct icp_qat_uclo_objhandle {int /*<<< orphan*/  str_table; } ;
struct icp_qat_fw_loader_handle {struct icp_qat_uclo_objhandle* obj_handle; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int ICP_QAT_UCLO_MAX_AE ; 
 scalar_t__ ICP_QAT_UOF_LOCAL_SCOPE ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 char* qat_uclo_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ qat_uclo_parse_num (char*,unsigned int*) ; 

__attribute__((used)) static int qat_uclo_fetch_initmem_ae(struct icp_qat_fw_loader_handle *handle,
				     struct icp_qat_uof_initmem *init_mem,
				     unsigned int size_range, unsigned int *ae)
{
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	char *str;

	if ((init_mem->addr + init_mem->num_in_bytes) > (size_range << 0x2)) {
		pr_err("QAT: initmem is out of range");
		return -EINVAL;
	}
	if (init_mem->scope != ICP_QAT_UOF_LOCAL_SCOPE) {
		pr_err("QAT: Memory scope for init_mem error\n");
		return -EINVAL;
	}
	str = qat_uclo_get_string(&obj_handle->str_table, init_mem->sym_name);
	if (!str) {
		pr_err("QAT: AE name assigned in UOF init table is NULL\n");
		return -EINVAL;
	}
	if (qat_uclo_parse_num(str, ae)) {
		pr_err("QAT: Parse num for AE number failed\n");
		return -EINVAL;
	}
	if (*ae >= ICP_QAT_UCLO_MAX_AE) {
		pr_err("QAT: ae %d out of range\n", *ae);
		return -EINVAL;
	}
	return 0;
}