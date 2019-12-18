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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPU3_PT_ORDER ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  set_memory_wb (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imgu_mmu_free_page_table(u32 *pt)
{
	set_memory_wb((unsigned long int)pt, IPU3_PT_ORDER);
	free_page((unsigned long)pt);
}