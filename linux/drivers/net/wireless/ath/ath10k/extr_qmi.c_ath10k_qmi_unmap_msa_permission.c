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
struct qcom_scm_vmperm {int /*<<< orphan*/  perm; int /*<<< orphan*/  vmid; } ;
struct ath10k_qmi {struct ath10k* ar; } ;
struct ath10k_msa_mem_info {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; int /*<<< orphan*/  secure; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QCOM_SCM_PERM_RW ; 
 int /*<<< orphan*/  QCOM_SCM_VMID_HLOS ; 
 int /*<<< orphan*/  QCOM_SCM_VMID_MSS_MSA ; 
 int /*<<< orphan*/  QCOM_SCM_VMID_WLAN ; 
 int /*<<< orphan*/  QCOM_SCM_VMID_WLAN_CE ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int qcom_scm_assign_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,struct qcom_scm_vmperm*,int) ; 

__attribute__((used)) static int ath10k_qmi_unmap_msa_permission(struct ath10k_qmi *qmi,
					   struct ath10k_msa_mem_info *mem_info)
{
	struct qcom_scm_vmperm dst_perms;
	struct ath10k *ar = qmi->ar;
	unsigned int src_perms;
	int ret;

	src_perms = BIT(QCOM_SCM_VMID_MSS_MSA) | BIT(QCOM_SCM_VMID_WLAN);

	if (!mem_info->secure)
		src_perms |= BIT(QCOM_SCM_VMID_WLAN_CE);

	dst_perms.vmid = QCOM_SCM_VMID_HLOS;
	dst_perms.perm = QCOM_SCM_PERM_RW;

	ret = qcom_scm_assign_mem(mem_info->addr, mem_info->size,
				  &src_perms, &dst_perms, 1);
	if (ret < 0)
		ath10k_err(ar, "failed to unmap msa permissions: %d\n", ret);

	return ret;
}