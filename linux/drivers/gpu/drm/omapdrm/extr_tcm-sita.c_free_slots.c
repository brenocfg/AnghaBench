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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (unsigned long*,unsigned long,int) ; 

__attribute__((used)) static void free_slots(unsigned long pos, u16 w, u16 h,
		unsigned long *map, u16 stride)
{
	int i;

	for (i = 0; i < h; i++, pos += stride)
		bitmap_clear(map, pos, w);
}