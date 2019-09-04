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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct ieee_ets {scalar_t__* prio_tc; int* tc_tsa; int /*<<< orphan*/ * tc_tx_bw; } ;
struct TYPE_4__ {scalar_t__* prio_tc; size_t num_tc; TYPE_1__* tc_info; } ;
struct hclge_dev {scalar_t__ tc_max; TYPE_2__ tm_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  tc_sch_mode; } ;

/* Variables and functions */
 scalar_t__ BW_PERCENT ; 
 int EINVAL ; 
 int /*<<< orphan*/  HCLGE_SCH_MODE_DWRR ; 
 int /*<<< orphan*/  HCLGE_SCH_MODE_SP ; 
 size_t HNAE3_MAX_TC ; 
#define  IEEE_8021QAZ_TSA_ETS 129 
#define  IEEE_8021QAZ_TSA_STRICT 128 

__attribute__((used)) static int hclge_ets_validate(struct hclge_dev *hdev, struct ieee_ets *ets,
			      u8 *tc, bool *changed)
{
	bool has_ets_tc = false;
	u32 total_ets_bw = 0;
	u8 max_tc = 0;
	u8 i;

	for (i = 0; i < HNAE3_MAX_TC; i++) {
		if (ets->prio_tc[i] >= hdev->tc_max ||
		    i >= hdev->tc_max)
			return -EINVAL;

		if (ets->prio_tc[i] != hdev->tm_info.prio_tc[i])
			*changed = true;

		if (ets->prio_tc[i] > max_tc)
			max_tc = ets->prio_tc[i];

		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_STRICT:
			if (hdev->tm_info.tc_info[i].tc_sch_mode !=
				HCLGE_SCH_MODE_SP)
				*changed = true;
			break;
		case IEEE_8021QAZ_TSA_ETS:
			if (hdev->tm_info.tc_info[i].tc_sch_mode !=
				HCLGE_SCH_MODE_DWRR)
				*changed = true;

			total_ets_bw += ets->tc_tx_bw[i];
			has_ets_tc = true;
			break;
		default:
			return -EINVAL;
		}
	}

	if (has_ets_tc && total_ets_bw != BW_PERCENT)
		return -EINVAL;

	*tc = max_tc + 1;
	if (*tc != hdev->tm_info.num_tc)
		*changed = true;

	return 0;
}