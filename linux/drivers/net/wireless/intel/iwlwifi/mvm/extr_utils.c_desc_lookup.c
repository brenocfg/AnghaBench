#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int num; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int FW_SYSASSERT_CPU_MASK ; 
 TYPE_1__* advanced_lookup ; 

__attribute__((used)) static const char *desc_lookup(u32 num)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(advanced_lookup) - 1; i++)
		if (advanced_lookup[i].num == (num & ~FW_SYSASSERT_CPU_MASK))
			return advanced_lookup[i].name;

	/* No entry matches 'num', so it is the last: ADVANCED_SYSASSERT */
	return advanced_lookup[i].name;
}