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
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mf_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_EN ; 
 int NIG_REG_LLH_FUNC_FILTER_EN_SIZE ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_VALUE ; 
 int /*<<< orphan*/  QED_MF_LLH_MAC_CLSS ; 
 int /*<<< orphan*/  qed_llh_mac_to_filter (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ qed_rd (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qed_llh_remove_mac_filter(struct qed_hwfn *p_hwfn,
			       struct qed_ptt *p_ptt, u8 *p_filter)
{
	u32 high = 0, low = 0;
	int i;

	if (!test_bit(QED_MF_LLH_MAC_CLSS, &p_hwfn->cdev->mf_bits))
		return;

	qed_llh_mac_to_filter(&high, &low, p_filter);

	/* Find the entry and clean it */
	for (i = 0; i < NIG_REG_LLH_FUNC_FILTER_EN_SIZE; i++) {
		if (qed_rd(p_hwfn, p_ptt,
			   NIG_REG_LLH_FUNC_FILTER_VALUE +
			   2 * i * sizeof(u32)) != low)
			continue;
		if (qed_rd(p_hwfn, p_ptt,
			   NIG_REG_LLH_FUNC_FILTER_VALUE +
			   (2 * i + 1) * sizeof(u32)) != high)
			continue;

		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_EN + i * sizeof(u32), 0);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_VALUE + 2 * i * sizeof(u32), 0);
		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_LLH_FUNC_FILTER_VALUE +
		       (2 * i + 1) * sizeof(u32), 0);

		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "mac: %pM is removed from %d\n",
			   p_filter, i);
		break;
	}
	if (i >= NIG_REG_LLH_FUNC_FILTER_EN_SIZE)
		DP_NOTICE(p_hwfn, "Tried to remove a non-configured filter\n");
}