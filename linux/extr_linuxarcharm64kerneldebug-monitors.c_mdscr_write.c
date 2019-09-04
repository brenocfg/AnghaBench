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
 int /*<<< orphan*/  local_daif_restore (unsigned long) ; 
 unsigned long local_daif_save () ; 
 int /*<<< orphan*/  mdscr_el1 ; 
 int /*<<< orphan*/  write_sysreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdscr_write(u32 mdscr)
{
	unsigned long flags;
	flags = local_daif_save();
	write_sysreg(mdscr, mdscr_el1);
	local_daif_restore(flags);
}