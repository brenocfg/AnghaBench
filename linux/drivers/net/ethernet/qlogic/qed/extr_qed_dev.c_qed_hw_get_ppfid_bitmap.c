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
typedef  int u8 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int rel_pf_id; struct qed_dev* cdev; } ;
struct qed_dev {int num_ports_in_engine; int ppfid_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*,int,int) ; 
 int EOPNOTSUPP ; 
 scalar_t__ QED_IS_BB (struct qed_dev*) ; 
 int qed_mcp_get_ppfid_bitmap (struct qed_hwfn*,struct qed_ptt*) ; 

__attribute__((used)) static int qed_hw_get_ppfid_bitmap(struct qed_hwfn *p_hwfn,
				   struct qed_ptt *p_ptt)
{
	struct qed_dev *cdev = p_hwfn->cdev;
	u8 native_ppfid_idx;
	int rc;

	/* Calculation of BB/AH is different for native_ppfid_idx */
	if (QED_IS_BB(cdev))
		native_ppfid_idx = p_hwfn->rel_pf_id;
	else
		native_ppfid_idx = p_hwfn->rel_pf_id /
		    cdev->num_ports_in_engine;

	rc = qed_mcp_get_ppfid_bitmap(p_hwfn, p_ptt);
	if (rc != 0 && rc != -EOPNOTSUPP)
		return rc;
	else if (rc == -EOPNOTSUPP)
		cdev->ppfid_bitmap = 0x1 << native_ppfid_idx;

	if (!(cdev->ppfid_bitmap & (0x1 << native_ppfid_idx))) {
		DP_INFO(p_hwfn,
			"Fix the PPFID bitmap to include the native PPFID [native_ppfid_idx %hhd, orig_bitmap 0x%hhx]\n",
			native_ppfid_idx, cdev->ppfid_bitmap);
		cdev->ppfid_bitmap = 0x1 << native_ppfid_idx;
	}

	return 0;
}