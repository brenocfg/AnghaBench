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
struct hnae3_handle {int /*<<< orphan*/  netdev_flags; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_FILTER_FE_EGRESS ; 
 int /*<<< orphan*/  HCLGE_FILTER_FE_EGRESS_V1_B ; 
 int /*<<< orphan*/  HCLGE_FILTER_FE_INGRESS ; 
 int /*<<< orphan*/  HCLGE_FILTER_TYPE_PORT ; 
 int /*<<< orphan*/  HCLGE_FILTER_TYPE_VF ; 
 int /*<<< orphan*/  HNAE3_VLAN_FLTR ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_set_vlan_filter_ctrl (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_enable_vlan_filter(struct hnae3_handle *handle, bool enable)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	if (hdev->pdev->revision >= 0x21) {
		hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_VF,
					   HCLGE_FILTER_FE_EGRESS, enable, 0);
		hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_PORT,
					   HCLGE_FILTER_FE_INGRESS, enable, 0);
	} else {
		hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_VF,
					   HCLGE_FILTER_FE_EGRESS_V1_B, enable,
					   0);
	}
	if (enable)
		handle->netdev_flags |= HNAE3_VLAN_FLTR;
	else
		handle->netdev_flags &= ~HNAE3_VLAN_FLTR;
}