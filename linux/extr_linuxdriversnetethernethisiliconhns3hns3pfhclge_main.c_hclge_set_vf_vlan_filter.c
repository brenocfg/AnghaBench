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
typedef  int u8 ;
typedef  int u16 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int num_alloc_vfs; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_set_vlan_filter_hw (struct hclge_dev*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_vf_vlan_filter(struct hnae3_handle *handle, int vfid,
				    u16 vlan, u8 qos, __be16 proto)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	if ((vfid >= hdev->num_alloc_vfs) || (vlan > 4095) || (qos > 7))
		return -EINVAL;
	if (proto != htons(ETH_P_8021Q))
		return -EPROTONOSUPPORT;

	return hclge_set_vlan_filter_hw(hdev, proto, vfid, vlan, qos, false);
}