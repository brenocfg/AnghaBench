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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_NIC_TYPE ; 

__attribute__((used)) static int find_dev_index(u32 nic_type)
{
	u8 index;

	index = (u8)(nic_type & 0x0000000f);
	if (index >= MAX_NIC_TYPE)
		return -EINVAL;

	return index;
}