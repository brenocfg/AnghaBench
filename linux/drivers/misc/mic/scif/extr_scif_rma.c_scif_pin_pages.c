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
typedef  int /*<<< orphan*/  scif_pinned_pages_t ;

/* Variables and functions */
 int __scif_pin_pages (void*,size_t,int*,int,int /*<<< orphan*/ *) ; 

int scif_pin_pages(void *addr, size_t len, int prot,
		   int map_flags, scif_pinned_pages_t *pages)
{
	return __scif_pin_pages(addr, len, &prot, map_flags, pages);
}