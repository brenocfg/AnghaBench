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
typedef  int u64 ;
typedef  int u16 ;
struct ksz_device {TYPE_1__* vlan_cache; } ;
struct TYPE_2__ {int* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  TABLE_VLAN ; 
 int VLAN_TABLE_S ; 
 int /*<<< orphan*/  ksz8795_r_table (struct ksz_device*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void ksz8795_r_vlan_entries(struct ksz_device *dev, u16 addr)
{
	u64 data;
	int i;

	ksz8795_r_table(dev, TABLE_VLAN, addr, &data);
	addr *= 4;
	for (i = 0; i < 4; i++) {
		dev->vlan_cache[addr + i].table[0] = (u16)data;
		data >>= VLAN_TABLE_S;
	}
}