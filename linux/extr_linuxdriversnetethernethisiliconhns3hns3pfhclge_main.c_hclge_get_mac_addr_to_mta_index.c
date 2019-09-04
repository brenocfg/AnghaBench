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
typedef  int u32 ;
typedef  int u16 ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int mta_mac_sel_type; } ;

/* Variables and functions */

__attribute__((used)) static u16 hclge_get_mac_addr_to_mta_index(struct hclge_vport *vport,
					   const u8 *addr)
{
	u16 high_val = addr[1] | (addr[0] << 8);
	struct hclge_dev *hdev = vport->back;
	u32 rsh = 4 - hdev->mta_mac_sel_type;
	u16 ret_val = (high_val >> rsh) & 0xfff;

	return ret_val;
}