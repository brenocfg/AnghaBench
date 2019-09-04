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
struct map_info {int dummy; } ;

/* Variables and functions */
 unsigned long DEVICE_ENABLE ; 
 int /*<<< orphan*/  PAGE_IO ; 
 unsigned long WINDOW_SHIFT ; 
 int /*<<< orphan*/  outw (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long page_in_window ; 

__attribute__((used)) static inline void sbc_gxx_page(struct map_info *map, unsigned long ofs)
{
	unsigned long page = ofs >> WINDOW_SHIFT;

	if( page!=page_in_window ) {
		outw( page | DEVICE_ENABLE, PAGE_IO );
		page_in_window = page;
	}
}