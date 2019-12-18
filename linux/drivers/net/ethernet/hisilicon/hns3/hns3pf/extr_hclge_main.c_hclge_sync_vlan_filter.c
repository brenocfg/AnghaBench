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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_vport {int /*<<< orphan*/  vlan_del_fail_bmap; int /*<<< orphan*/  vport_id; } ;
struct hclge_dev {int num_alloc_vport; struct hclge_vport* vport; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int HCLGE_MAX_SYNC_COUNT ; 
 int /*<<< orphan*/  VLAN_N_VID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_rm_vport_vlan_table (struct hclge_vport*,int /*<<< orphan*/ ,int) ; 
 int hclge_set_vlan_filter_hw (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_sync_vlan_filter(struct hclge_dev *hdev)
{
#define HCLGE_MAX_SYNC_COUNT	60

	int i, ret, sync_cnt = 0;
	u16 vlan_id;

	/* start from vport 1 for PF is always alive */
	for (i = 0; i < hdev->num_alloc_vport; i++) {
		struct hclge_vport *vport = &hdev->vport[i];

		vlan_id = find_first_bit(vport->vlan_del_fail_bmap,
					 VLAN_N_VID);
		while (vlan_id != VLAN_N_VID) {
			ret = hclge_set_vlan_filter_hw(hdev, htons(ETH_P_8021Q),
						       vport->vport_id, vlan_id,
						       true);
			if (ret && ret != -EINVAL)
				return;

			clear_bit(vlan_id, vport->vlan_del_fail_bmap);
			hclge_rm_vport_vlan_table(vport, vlan_id, false);

			sync_cnt++;
			if (sync_cnt >= HCLGE_MAX_SYNC_COUNT)
				return;

			vlan_id = find_first_bit(vport->vlan_del_fail_bmap,
						 VLAN_N_VID);
		}
	}
}