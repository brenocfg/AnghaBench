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
typedef  size_t u8 ;
struct ieee_ets {int* tc_tsa; int /*<<< orphan*/  prio_tc; int /*<<< orphan*/ * tc_tx_bw; } ;
struct TYPE_6__ {TYPE_2__* pg_info; TYPE_1__* tc_info; } ;
struct hclge_dev {TYPE_3__ tm_info; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tc_dwrr; } ;
struct TYPE_4__ {int /*<<< orphan*/  tc_sch_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCLGE_SCH_MODE_DWRR ; 
 int /*<<< orphan*/  HCLGE_SCH_MODE_SP ; 
 size_t HNAE3_MAX_TC ; 
#define  IEEE_8021QAZ_TSA_ETS 129 
#define  IEEE_8021QAZ_TSA_STRICT 128 
 int /*<<< orphan*/  hclge_tm_prio_tc_info_update (struct hclge_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_ieee_ets_to_tm_info(struct hclge_dev *hdev,
				     struct ieee_ets *ets)
{
	u8 i;

	for (i = 0; i < HNAE3_MAX_TC; i++) {
		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_STRICT:
			hdev->tm_info.tc_info[i].tc_sch_mode =
				HCLGE_SCH_MODE_SP;
			hdev->tm_info.pg_info[0].tc_dwrr[i] = 0;
			break;
		case IEEE_8021QAZ_TSA_ETS:
			hdev->tm_info.tc_info[i].tc_sch_mode =
				HCLGE_SCH_MODE_DWRR;
			hdev->tm_info.pg_info[0].tc_dwrr[i] =
				ets->tc_tx_bw[i];
			break;
		default:
			/* Hardware only supports SP (strict priority)
			 * or ETS (enhanced transmission selection)
			 * algorithms, if we receive some other value
			 * from dcbnl, then throw an error.
			 */
			return -EINVAL;
		}
	}

	hclge_tm_prio_tc_info_update(hdev, ets->prio_tc);

	return 0;
}