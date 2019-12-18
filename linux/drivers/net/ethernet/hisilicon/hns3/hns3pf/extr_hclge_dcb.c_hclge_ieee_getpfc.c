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
typedef  size_t u8 ;
typedef  void* u64 ;
struct ieee_pfc {size_t pfc_en; void** indications; void** requests; int /*<<< orphan*/  pfc_cap; } ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_2__ {size_t* prio_tc; size_t hw_pfc_map; size_t num_tc; } ;
struct hclge_dev {TYPE_1__ tm_info; int /*<<< orphan*/  pfc_max; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 size_t HCLGE_MAX_TC_NUM ; 
 int HNAE3_MAX_TC ; 
 size_t HNAE3_MAX_USER_PRIO ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_pfc_rx_stats_get (struct hclge_dev*,void**) ; 
 int hclge_pfc_tx_stats_get (struct hclge_dev*,void**) ; 
 int /*<<< orphan*/  memset (struct ieee_pfc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_ieee_getpfc(struct hnae3_handle *h, struct ieee_pfc *pfc)
{
	u64 requests[HNAE3_MAX_TC], indications[HNAE3_MAX_TC];
	struct hclge_vport *vport = hclge_get_vport(h);
	struct hclge_dev *hdev = vport->back;
	u8 i, j, pfc_map, *prio_tc;
	int ret;

	memset(pfc, 0, sizeof(*pfc));
	pfc->pfc_cap = hdev->pfc_max;
	prio_tc = hdev->tm_info.prio_tc;
	pfc_map = hdev->tm_info.hw_pfc_map;

	/* Pfc setting is based on TC */
	for (i = 0; i < hdev->tm_info.num_tc; i++) {
		for (j = 0; j < HNAE3_MAX_USER_PRIO; j++) {
			if ((prio_tc[j] == i) && (pfc_map & BIT(i)))
				pfc->pfc_en |= BIT(j);
		}
	}

	ret = hclge_pfc_tx_stats_get(hdev, requests);
	if (ret)
		return ret;

	ret = hclge_pfc_rx_stats_get(hdev, indications);
	if (ret)
		return ret;

	for (i = 0; i < HCLGE_MAX_TC_NUM; i++) {
		pfc->requests[i] = requests[i];
		pfc->indications[i] = indications[i];
	}
	return 0;
}