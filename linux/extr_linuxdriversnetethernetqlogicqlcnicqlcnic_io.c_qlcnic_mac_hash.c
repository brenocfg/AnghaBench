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
typedef  int u64 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline u8 qlcnic_mac_hash(u64 mac, u16 vlan)
{
	return (u8)((mac & 0xff) ^ ((mac >> 40) & 0xff) ^ (vlan & 0xff));
}