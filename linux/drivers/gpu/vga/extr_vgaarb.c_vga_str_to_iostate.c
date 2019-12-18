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
 int VGA_RSRC_LEGACY_IO ; 
 int VGA_RSRC_LEGACY_MEM ; 
 int VGA_RSRC_NONE ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int vga_str_to_iostate(char *buf, int str_size, int *io_state)
{
	/* we could in theory hand out locks on IO and mem
	 * separately to userspace but it can cause deadlocks */
	if (strncmp(buf, "none", 4) == 0) {
		*io_state = VGA_RSRC_NONE;
		return 1;
	}

	/* XXX We're not chekcing the str_size! */
	if (strncmp(buf, "io+mem", 6) == 0)
		goto both;
	else if (strncmp(buf, "io", 2) == 0)
		goto both;
	else if (strncmp(buf, "mem", 3) == 0)
		goto both;
	return 0;
both:
	*io_state = VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;
	return 1;
}