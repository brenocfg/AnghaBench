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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_FILTER_TYPE_VF ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_set_vlan_filter_ctrl (struct hclge_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hclge_enable_vlan_filter(struct hnae3_handle *handle, bool enable)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	hclge_set_vlan_filter_ctrl(hdev, HCLGE_FILTER_TYPE_VF, enable);
}