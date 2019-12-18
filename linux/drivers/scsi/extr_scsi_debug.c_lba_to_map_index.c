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
typedef  unsigned long sector_t ;

/* Variables and functions */
 scalar_t__ sdebug_unmap_alignment ; 
 scalar_t__ sdebug_unmap_granularity ; 
 int /*<<< orphan*/  sector_div (unsigned long,scalar_t__) ; 

__attribute__((used)) static unsigned long lba_to_map_index(sector_t lba)
{
	if (sdebug_unmap_alignment)
		lba += sdebug_unmap_granularity - sdebug_unmap_alignment;
	sector_div(lba, sdebug_unmap_granularity);
	return lba;
}