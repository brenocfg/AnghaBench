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
typedef  int u32 ;

/* Variables and functions */
 int RSZ_DATA_STEP (int) ; 
 int RSZ_PARA_STEP (int) ; 

__attribute__((used)) static inline u32 rsz_step_value(u32 src, u32 dst)
{
	u32 val = 0;

	if (src == dst)
		val = 0;
	else if (src < dst)
		val = RSZ_PARA_STEP((src << 16) / dst);
	else if (src > dst)
		val = RSZ_DATA_STEP(src / dst) |
		      RSZ_PARA_STEP(((src << 16) / dst) & 0xffff);

	return val;
}