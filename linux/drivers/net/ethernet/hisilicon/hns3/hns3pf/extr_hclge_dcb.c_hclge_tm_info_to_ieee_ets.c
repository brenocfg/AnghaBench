#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct ieee_ets {int willing; int /*<<< orphan*/ * tc_tsa; int /*<<< orphan*/ * tc_tx_bw; int /*<<< orphan*/ * prio_tc; int /*<<< orphan*/  ets_cap; } ;
struct TYPE_6__ {TYPE_2__* tc_info; TYPE_1__* pg_info; int /*<<< orphan*/ * prio_tc; } ;
struct hclge_dev {TYPE_3__ tm_info; int /*<<< orphan*/  tc_max; } ;
struct TYPE_5__ {scalar_t__ tc_sch_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tc_dwrr; } ;

/* Variables and functions */
 scalar_t__ HCLGE_SCH_MODE_SP ; 
 size_t HNAE3_MAX_TC ; 
 int /*<<< orphan*/  IEEE_8021QAZ_TSA_ETS ; 
 int /*<<< orphan*/  IEEE_8021QAZ_TSA_STRICT ; 
 int /*<<< orphan*/  memset (struct ieee_ets*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hclge_tm_info_to_ieee_ets(struct hclge_dev *hdev,
				      struct ieee_ets *ets)
{
	u32 i;

	memset(ets, 0, sizeof(*ets));
	ets->willing = 1;
	ets->ets_cap = hdev->tc_max;

	for (i = 0; i < HNAE3_MAX_TC; i++) {
		ets->prio_tc[i] = hdev->tm_info.prio_tc[i];
		ets->tc_tx_bw[i] = hdev->tm_info.pg_info[0].tc_dwrr[i];

		if (hdev->tm_info.tc_info[i].tc_sch_mode ==
		    HCLGE_SCH_MODE_SP)
			ets->tc_tsa[i] = IEEE_8021QAZ_TSA_STRICT;
		else
			ets->tc_tsa[i] = IEEE_8021QAZ_TSA_ETS;
	}
}