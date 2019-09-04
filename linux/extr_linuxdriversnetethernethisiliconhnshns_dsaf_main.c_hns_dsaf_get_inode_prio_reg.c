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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int DSAF_INODE_IN_PRIO_PAUSE_BASE_OFFSET ; 
 scalar_t__ DSAF_INODE_IN_PRIO_PAUSE_BASE_REG ; 
 int DSAF_INODE_IN_PRIO_PAUSE_OFFSET ; 
 int DSAF_REG_PER_ZONE ; 

__attribute__((used)) static u32 hns_dsaf_get_inode_prio_reg(int index)
{
	int base_index, offset;
	u32 base_addr = DSAF_INODE_IN_PRIO_PAUSE_BASE_REG;

	base_index = (index + 1) / DSAF_REG_PER_ZONE;
	offset = (index + 1) % DSAF_REG_PER_ZONE;

	return base_addr + DSAF_INODE_IN_PRIO_PAUSE_BASE_OFFSET * base_index +
		DSAF_INODE_IN_PRIO_PAUSE_OFFSET * offset;
}