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

/* Variables and functions */
 int down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efivars_lock ; 

int efivar_entry_iter_begin(void)
{
	return down_interruptible(&efivars_lock);
}