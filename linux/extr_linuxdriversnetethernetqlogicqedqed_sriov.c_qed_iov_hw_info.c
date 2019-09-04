#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct qed_hwfn {int abs_pf_id; struct qed_dev* cdev; } ;
struct qed_dev {TYPE_1__* p_iov_info; int /*<<< orphan*/  pdev; } ;
struct TYPE_3__ {int pos; int offset; void* first_vf_in_pf; int /*<<< orphan*/  total_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_VF (struct qed_dev*) ; 
 scalar_t__ MAX_NUM_VFS_BB ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 scalar_t__ QED_PATH_ID (struct qed_hwfn*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pci_find_ext_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qed_iov_pci_cfg_info (struct qed_dev*) ; 

int qed_iov_hw_info(struct qed_hwfn *p_hwfn)
{
	struct qed_dev *cdev = p_hwfn->cdev;
	int pos;
	int rc;

	if (IS_VF(p_hwfn->cdev))
		return 0;

	/* Learn the PCI configuration */
	pos = pci_find_ext_capability(p_hwfn->cdev->pdev,
				      PCI_EXT_CAP_ID_SRIOV);
	if (!pos) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV, "No PCIe IOV support\n");
		return 0;
	}

	/* Allocate a new struct for IOV information */
	cdev->p_iov_info = kzalloc(sizeof(*cdev->p_iov_info), GFP_KERNEL);
	if (!cdev->p_iov_info)
		return -ENOMEM;

	cdev->p_iov_info->pos = pos;

	rc = qed_iov_pci_cfg_info(cdev);
	if (rc)
		return rc;

	/* We want PF IOV to be synonemous with the existance of p_iov_info;
	 * In case the capability is published but there are no VFs, simply
	 * de-allocate the struct.
	 */
	if (!cdev->p_iov_info->total_vfs) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "IOV capabilities, but no VFs are published\n");
		kfree(cdev->p_iov_info);
		cdev->p_iov_info = NULL;
		return 0;
	}

	/* First VF index based on offset is tricky:
	 *  - If ARI is supported [likely], offset - (16 - pf_id) would
	 *    provide the number for eng0. 2nd engine Vfs would begin
	 *    after the first engine's VFs.
	 *  - If !ARI, VFs would start on next device.
	 *    so offset - (256 - pf_id) would provide the number.
	 * Utilize the fact that (256 - pf_id) is achieved only by later
	 * to differentiate between the two.
	 */

	if (p_hwfn->cdev->p_iov_info->offset < (256 - p_hwfn->abs_pf_id)) {
		u32 first = p_hwfn->cdev->p_iov_info->offset +
			    p_hwfn->abs_pf_id - 16;

		cdev->p_iov_info->first_vf_in_pf = first;

		if (QED_PATH_ID(p_hwfn))
			cdev->p_iov_info->first_vf_in_pf -= MAX_NUM_VFS_BB;
	} else {
		u32 first = p_hwfn->cdev->p_iov_info->offset +
			    p_hwfn->abs_pf_id - 256;

		cdev->p_iov_info->first_vf_in_pf = first;
	}

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "First VF in hwfn 0x%08x\n",
		   cdev->p_iov_info->first_vf_in_pf);

	return 0;
}