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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R4K_INDEX ; 
 int /*<<< orphan*/  cpu_has_dc_aliases ; 
 int /*<<< orphan*/  local_r4k_flush_cache_mm ; 
 int /*<<< orphan*/  r4k_on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_struct*) ; 

__attribute__((used)) static void r4k_flush_cache_mm(struct mm_struct *mm)
{
	if (!cpu_has_dc_aliases)
		return;

	r4k_on_each_cpu(R4K_INDEX, local_r4k_flush_cache_mm, mm);
}