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
 int /*<<< orphan*/  get_pvr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr ; 

int kgdb_arch_init(void)
{
	get_pvr(&pvr); /* Fill PVR structure */
	return 0;
}