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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMD_SIZE ; 
 int /*<<< orphan*/  kernel_ident_mapping_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mapping_info ; 
 unsigned long round_down (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long round_up (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ top_level_pgt ; 

void add_identity_map(unsigned long start, unsigned long size)
{
	unsigned long end = start + size;

	/* Align boundary to 2M. */
	start = round_down(start, PMD_SIZE);
	end = round_up(end, PMD_SIZE);
	if (start >= end)
		return;

	/* Build the mapping. */
	kernel_ident_mapping_init(&mapping_info, (pgd_t *)top_level_pgt,
				  start, end);
}