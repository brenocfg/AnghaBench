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
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int hclge_cfg_mac_speed_dup (struct hclge_dev*,int,int /*<<< orphan*/ ) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static int hclge_cfg_mac_speed_dup_h(struct hnae3_handle *handle, int speed,
				     u8 duplex)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	return hclge_cfg_mac_speed_dup(hdev, speed, duplex);
}