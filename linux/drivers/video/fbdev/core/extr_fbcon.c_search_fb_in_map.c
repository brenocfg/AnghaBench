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
 int* con2fb_map ; 
 int first_fb_vc ; 
 int last_fb_vc ; 

__attribute__((used)) static int search_fb_in_map(int idx)
{
	int i, retval = 0;

	for (i = first_fb_vc; i <= last_fb_vc; i++) {
		if (con2fb_map[i] == idx)
			retval = 1;
	}
	return retval;
}