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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
union qed_llh_filter {TYPE_1__ mac; } ;
typedef  int u8 ;
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {int /*<<< orphan*/  mf_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,int*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int*,int,int,int,int) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_LLH_FILTER_TYPE_MAC ; 
 int /*<<< orphan*/  QED_MF_LLH_MAC_CLSS ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int qed_llh_abs_ppfid (struct qed_dev*,int,int*) ; 
 int qed_llh_add_filter (struct qed_hwfn*,struct qed_ptt*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int qed_llh_shadow_add_filter (struct qed_dev*,int,int /*<<< orphan*/ ,union qed_llh_filter*,int*,int*) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qed_llh_add_mac_filter(struct qed_dev *cdev,
			   u8 ppfid, u8 mac_addr[ETH_ALEN])
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	union qed_llh_filter filter = {};
	u8 filter_idx, abs_ppfid;
	u32 high, low, ref_cnt;
	int rc = 0;

	if (!p_ptt)
		return -EAGAIN;

	if (!test_bit(QED_MF_LLH_MAC_CLSS, &cdev->mf_bits))
		goto out;

	memcpy(filter.mac.addr, mac_addr, ETH_ALEN);
	rc = qed_llh_shadow_add_filter(cdev, ppfid,
				       QED_LLH_FILTER_TYPE_MAC,
				       &filter, &filter_idx, &ref_cnt);
	if (rc)
		goto err;

	/* Configure the LLH only in case of a new the filter */
	if (ref_cnt == 1) {
		rc = qed_llh_abs_ppfid(cdev, ppfid, &abs_ppfid);
		if (rc)
			goto err;

		high = mac_addr[1] | (mac_addr[0] << 8);
		low = mac_addr[5] | (mac_addr[4] << 8) | (mac_addr[3] << 16) |
		      (mac_addr[2] << 24);
		rc = qed_llh_add_filter(p_hwfn, p_ptt, abs_ppfid, filter_idx,
					0, high, low);
		if (rc)
			goto err;
	}

	DP_VERBOSE(cdev,
		   QED_MSG_SP,
		   "LLH: Added MAC filter [%pM] to ppfid %hhd [abs %hhd] at idx %hhd [ref_cnt %d]\n",
		   mac_addr, ppfid, abs_ppfid, filter_idx, ref_cnt);

	goto out;

err:	DP_NOTICE(cdev,
		  "LLH: Failed to add MAC filter [%pM] to ppfid %hhd\n",
		  mac_addr, ppfid);
out:
	qed_ptt_release(p_hwfn, p_ptt);

	return rc;
}