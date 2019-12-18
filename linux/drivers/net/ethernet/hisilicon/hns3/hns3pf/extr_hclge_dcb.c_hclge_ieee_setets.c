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
struct net_device {int dummy; } ;
struct ieee_ets {int dummy; } ;
struct TYPE_2__ {struct net_device* netdev; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int dcbx_cap; int flag; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_VER_IEEE ; 
 int EINVAL ; 
 int HCLGE_FLAG_MQPRIO_ENABLE ; 
 int /*<<< orphan*/  drv ; 
 int hclge_client_setup_tc (struct hclge_dev*) ; 
 int hclge_ets_validate (struct hclge_dev*,struct ieee_ets*,int /*<<< orphan*/ *,int*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_ieee_ets_to_tm_info (struct hclge_dev*,struct ieee_ets*) ; 
 int hclge_map_update (struct hclge_dev*) ; 
 int hclge_notify_down_uinit (struct hclge_dev*) ; 
 int hclge_notify_init_up (struct hclge_dev*) ; 
 int hclge_tm_dwrr_cfg (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_tm_schd_info_update (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct hnae3_handle*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static int hclge_ieee_setets(struct hnae3_handle *h, struct ieee_ets *ets)
{
	struct hclge_vport *vport = hclge_get_vport(h);
	struct net_device *netdev = h->kinfo.netdev;
	struct hclge_dev *hdev = vport->back;
	bool map_changed = false;
	u8 num_tc = 0;
	int ret;

	if (!(hdev->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    hdev->flag & HCLGE_FLAG_MQPRIO_ENABLE)
		return -EINVAL;

	ret = hclge_ets_validate(hdev, ets, &num_tc, &map_changed);
	if (ret)
		return ret;

	if (map_changed) {
		netif_dbg(h, drv, netdev, "set ets\n");

		ret = hclge_notify_down_uinit(hdev);
		if (ret)
			return ret;
	}

	hclge_tm_schd_info_update(hdev, num_tc);

	ret = hclge_ieee_ets_to_tm_info(hdev, ets);
	if (ret)
		goto err_out;

	if (map_changed) {
		ret = hclge_map_update(hdev);
		if (ret)
			goto err_out;

		ret = hclge_client_setup_tc(hdev);
		if (ret)
			goto err_out;

		ret = hclge_notify_init_up(hdev);
		if (ret)
			return ret;
	}

	return hclge_tm_dwrr_cfg(hdev);

err_out:
	if (!map_changed)
		return ret;

	hclge_notify_init_up(hdev);

	return ret;
}