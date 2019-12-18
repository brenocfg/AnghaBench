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
 int ICM_PORT_INDEX_SHIFT ; 
 int ICM_PORT_TYPE_MASK ; 
 int TB_TYPE_PORT ; 

__attribute__((used)) static inline int icm_fr_get_switch_index(u32 port)
{
	int index;

	if ((port & ICM_PORT_TYPE_MASK) != TB_TYPE_PORT)
		return 0;

	index = port >> ICM_PORT_INDEX_SHIFT;
	return index != 0xff ? index : 0;
}