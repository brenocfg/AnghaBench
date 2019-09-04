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
struct cbe_pmd_shadow_regs {int dummy; } ;
struct cbe_regs_map {struct cbe_pmd_shadow_regs pmd_shadow_regs; } ;
struct TYPE_2__ {struct cbe_regs_map* regs; } ;

/* Variables and functions */
 TYPE_1__* cbe_thread_map ; 

struct cbe_pmd_shadow_regs *cbe_get_cpu_pmd_shadow_regs(int cpu)
{
	struct cbe_regs_map *map = cbe_thread_map[cpu].regs;
	if (map == NULL)
		return NULL;
	return &map->pmd_shadow_regs;
}