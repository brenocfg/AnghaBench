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
struct net_device {int dummy; } ;
struct ieee_pfc {size_t pfc_en; } ;
struct TYPE_3__ {struct net_device* netdev; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_4__ {size_t pfc_en; size_t* prio_tc; size_t num_tc; size_t hw_pfc_map; } ;
struct hclge_dev {int dcbx_cap; int flag; TYPE_2__ tm_info; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 int DCB_CAP_DCBX_VER_IEEE ; 
 int EINVAL ; 
 int HCLGE_FLAG_MQPRIO_ENABLE ; 
 size_t HNAE3_MAX_USER_PRIO ; 
 int /*<<< orphan*/  drv ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_pause_setup_hw (struct hclge_dev*,int) ; 
 int /*<<< orphan*/  hclge_tm_pfc_info_update (struct hclge_dev*) ; 
 int /*<<< orphan*/  netif_dbg (struct hnae3_handle*,int /*<<< orphan*/ ,struct net_device*,char*,size_t,size_t,size_t) ; 

__attribute__((used)) static int hclge_ieee_setpfc(struct hnae3_handle *h, struct ieee_pfc *pfc)
{
	struct hclge_vport *vport = hclge_get_vport(h);
	struct net_device *netdev = h->kinfo.netdev;
	struct hclge_dev *hdev = vport->back;
	u8 i, j, pfc_map, *prio_tc;

	if (!(hdev->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    hdev->flag & HCLGE_FLAG_MQPRIO_ENABLE)
		return -EINVAL;

	if (pfc->pfc_en == hdev->tm_info.pfc_en)
		return 0;

	prio_tc = hdev->tm_info.prio_tc;
	pfc_map = 0;

	for (i = 0; i < hdev->tm_info.num_tc; i++) {
		for (j = 0; j < HNAE3_MAX_USER_PRIO; j++) {
			if ((prio_tc[j] == i) && (pfc->pfc_en & BIT(j))) {
				pfc_map |= BIT(i);
				break;
			}
		}
	}

	hdev->tm_info.hw_pfc_map = pfc_map;
	hdev->tm_info.pfc_en = pfc->pfc_en;

	netif_dbg(h, drv, netdev,
		  "set pfc: pfc_en=%x, pfc_map=%x, num_tc=%u\n",
		  pfc->pfc_en, pfc_map, hdev->tm_info.num_tc);

	hclge_tm_pfc_info_update(hdev);

	return hclge_pause_setup_hw(hdev, false);
}