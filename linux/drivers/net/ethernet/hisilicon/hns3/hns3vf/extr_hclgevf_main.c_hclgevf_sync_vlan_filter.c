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
typedef  scalar_t__ u16 ;
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int /*<<< orphan*/  vlan_del_fail_bmap; struct hnae3_handle nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int HCLGEVF_MAX_SYNC_COUNT ; 
 scalar_t__ VLAN_N_VID ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int hclgevf_set_vlan_filter (struct hnae3_handle*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclgevf_sync_vlan_filter(struct hclgevf_dev *hdev)
{
#define HCLGEVF_MAX_SYNC_COUNT	60
	struct hnae3_handle *handle = &hdev->nic;
	int ret, sync_cnt = 0;
	u16 vlan_id;

	vlan_id = find_first_bit(hdev->vlan_del_fail_bmap, VLAN_N_VID);
	while (vlan_id != VLAN_N_VID) {
		ret = hclgevf_set_vlan_filter(handle, htons(ETH_P_8021Q),
					      vlan_id, true);
		if (ret)
			return;

		clear_bit(vlan_id, hdev->vlan_del_fail_bmap);
		sync_cnt++;
		if (sync_cnt >= HCLGEVF_MAX_SYNC_COUNT)
			return;

		vlan_id = find_first_bit(hdev->vlan_del_fail_bmap, VLAN_N_VID);
	}
}