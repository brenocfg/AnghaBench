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
 int /*<<< orphan*/  WB_SIO_EXT_EXIT_KEY ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  release_region (unsigned long,int) ; 

__attribute__((used)) static void winbond_sio_leave(unsigned long base)
{
	outb(WB_SIO_EXT_EXIT_KEY, base);

	release_region(base, 2);
}