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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TABLE_VLAN ; 
 int /*<<< orphan*/  ksz8795_r_table (struct ksz_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ksz8795_r_vlan_table(struct ksz_device *dev, u16 vid, u16 *vlan)
{
	int index;
	u16 *data;
	u16 addr;
	u64 buf;

	data = (u16 *)&buf;
	addr = vid / 4;
	index = vid & 3;
	ksz8795_r_table(dev, TABLE_VLAN, addr, &buf);
	*vlan = data[index];
}