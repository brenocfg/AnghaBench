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
typedef  int /*<<< orphan*/  u8 ;
struct ieee_ets {int dummy; } ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int dcbx_cap; int flag; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_VER_IEEE ; 
 int EINVAL ; 
 int HCLGE_FLAG_MQPRIO_ENABLE ; 
 int hclge_client_setup_tc (struct hclge_dev*) ; 
 int hclge_ets_validate (struct hclge_dev*,struct ieee_ets*,int /*<<< orphan*/ *,int*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_ieee_ets_to_tm_info (struct hclge_dev*,struct ieee_ets*) ; 
 int hclge_tm_dwrr_cfg (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_tm_schd_info_update (struct hclge_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_ieee_setets(struct hnae3_handle *h, struct ieee_ets *ets)
{
	struct hclge_vport *vport = hclge_get_vport(h);
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

	hclge_tm_schd_info_update(hdev, num_tc);

	ret = hclge_ieee_ets_to_tm_info(hdev, ets);
	if (ret)
		return ret;

	if (map_changed) {
		ret = hclge_client_setup_tc(hdev);
		if (ret)
			return ret;
	}

	return hclge_tm_dwrr_cfg(hdev);
}