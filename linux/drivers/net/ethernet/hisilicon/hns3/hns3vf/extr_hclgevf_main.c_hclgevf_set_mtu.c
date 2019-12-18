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
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int dummy; } ;
typedef  int /*<<< orphan*/  new_mtu ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MBX_SET_MTU ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_set_mtu(struct hnae3_handle *handle, int new_mtu)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	return hclgevf_send_mbx_msg(hdev, HCLGE_MBX_SET_MTU, 0, (u8 *)&new_mtu,
				    sizeof(new_mtu), true, NULL, 0);
}