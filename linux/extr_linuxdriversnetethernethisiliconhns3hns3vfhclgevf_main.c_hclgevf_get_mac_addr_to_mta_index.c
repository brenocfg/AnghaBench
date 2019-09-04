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
struct hclgevf_dev {int mta_mac_sel_type; } ;

/* Variables and functions */
 int HCLGEVF_MTA_TYPE_SEL_MAX ; 

__attribute__((used)) static u16 hclgevf_get_mac_addr_to_mta_index(struct hclgevf_dev *hdev,
					     const u8 *addr)
{
	u32 rsh = HCLGEVF_MTA_TYPE_SEL_MAX - hdev->mta_mac_sel_type;
	u16 high_val = addr[1] | (addr[0] << 8);

	return (high_val >> rsh) & 0xfff;
}