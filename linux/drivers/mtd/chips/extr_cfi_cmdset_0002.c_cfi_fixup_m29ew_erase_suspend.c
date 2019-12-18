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
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (int) ; 
 scalar_t__ is_m29ew (struct cfi_private*) ; 
 int /*<<< orphan*/  map_write (struct map_info*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void cfi_fixup_m29ew_erase_suspend(struct map_info *map,
					  unsigned long adr)
{
	struct cfi_private *cfi = map->fldrv_priv;
	/* before resume, insert a dummy 0xF0 cycle for Micron M29EW devices */
	if (is_m29ew(cfi))
		map_write(map, CMD(0xF0), adr);
}