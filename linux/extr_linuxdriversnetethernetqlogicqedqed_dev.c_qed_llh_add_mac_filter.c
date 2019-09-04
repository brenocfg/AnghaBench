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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mf_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_EN ; 
 int NIG_REG_LLH_FUNC_FILTER_EN_SIZE ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_MODE ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_VALUE ; 
 int /*<<< orphan*/  QED_MF_LLH_MAC_CLSS ; 
 int /*<<< orphan*/  qed_llh_mac_to_filter (int*,int*,int /*<<< orphan*/ *) ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qed_llh_add_mac_filter(struct qed_hwfn *p_hwfn,
			   struct qed_ptt *p_ptt, u8 *p_filter)
{
	u32 high = 0, low = 0, en;
	int i;

	if (!test_bit(QED_MF_LLH_MAC_CLSS, &p_hwfn->cdev->mf_bits))
		return 0;

	qed_llh_mac_to_filter(&high, &low, p_filter);

	/* Find a free entry and utilize it */
	for (i = 0; i < NIG_REG_LLH_FUNC_FILTER_EN_SIZE; i++) {
		en = qed_rd(p_hwfn, p_ptt,
			    NIG_REG_LLH_FUNC_FILTER_EN + i * sizeof(u32));
		if (en)
			continue;
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_VALUE +
		       2 * i * sizeof(u32), low);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_VALUE +
		       (2 * i + 1) * sizeof(u32), high);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_MODE + i * sizeof(u32), 0);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE +
		       i * sizeof(u32), 0);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_EN + i * sizeof(u32), 1);
		break;
	}
	if (i >= NIG_REG_LLH_FUNC_FILTER_EN_SIZE) {
		DP_NOTICE(p_hwfn,
			  "Failed to find an empty LLH filter to utilize\n");
		return -EINVAL;
	}

	DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
		   "mac: %pM is added at %d\n",
		   p_filter, i);

	return 0;
}