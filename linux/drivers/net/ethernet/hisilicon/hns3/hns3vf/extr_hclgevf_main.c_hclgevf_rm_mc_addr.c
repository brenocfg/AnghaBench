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
struct hclgevf_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_MC_REMOVE ; 
 int /*<<< orphan*/  HCLGE_MBX_SET_MULTICAST ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_rm_mc_addr(struct hnae3_handle *handle,
			      const unsigned char *addr)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	return hclgevf_send_mbx_msg(hdev, HCLGE_MBX_SET_MULTICAST,
				    HCLGE_MBX_MAC_VLAN_MC_REMOVE,
				    addr, ETH_ALEN, false, NULL, 0);
}