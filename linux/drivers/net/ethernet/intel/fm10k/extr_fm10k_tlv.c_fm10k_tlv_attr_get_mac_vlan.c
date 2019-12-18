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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

s32 fm10k_tlv_attr_get_mac_vlan(u32 *attr, u8 *mac_addr, u16 *vlan)
{
	/* verify pointers are not NULL */
	if (!mac_addr || !attr)
		return FM10K_ERR_PARAM;

	*(__le32 *)&mac_addr[0] = cpu_to_le32(attr[1]);
	*(__le16 *)&mac_addr[4] = cpu_to_le16((u16)(attr[2]));
	*vlan = (u16)(attr[2] >> 16);

	return 0;
}