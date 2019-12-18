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
 unsigned int mda_cursor_loc ; 
 int /*<<< orphan*/  write_mda_w (unsigned int,int) ; 

__attribute__((used)) static inline void mda_set_cursor(unsigned int location) 
{
	if (mda_cursor_loc == location)
		return;

	write_mda_w(location >> 1, 0x0e);

	mda_cursor_loc = location;
}