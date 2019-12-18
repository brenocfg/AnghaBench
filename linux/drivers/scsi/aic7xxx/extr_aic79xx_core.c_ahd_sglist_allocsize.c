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
typedef  int u_int ;
struct ahd_softc {int dummy; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int AHD_SCB_MAX_ALLOC ; 
 int PAGE_SIZE ; 
 int ahd_sglist_size (struct ahd_softc*) ; 
 int roundup (int,int) ; 

__attribute__((used)) static u_int
ahd_sglist_allocsize(struct ahd_softc *ahd)
{
	bus_size_t sg_list_increment;
	bus_size_t sg_list_size;
	bus_size_t max_list_size;
	bus_size_t best_list_size;

	/* Start out with the minimum required for AHD_NSEG. */
	sg_list_increment = ahd_sglist_size(ahd);
	sg_list_size = sg_list_increment;

	/* Get us as close as possible to a page in size. */
	while ((sg_list_size + sg_list_increment) <= PAGE_SIZE)
		sg_list_size += sg_list_increment;

	/*
	 * Try to reduce the amount of wastage by allocating
	 * multiple pages.
	 */
	best_list_size = sg_list_size;
	max_list_size = roundup(sg_list_increment, PAGE_SIZE);
	if (max_list_size < 4 * PAGE_SIZE)
		max_list_size = 4 * PAGE_SIZE;
	if (max_list_size > (AHD_SCB_MAX_ALLOC * sg_list_increment))
		max_list_size = (AHD_SCB_MAX_ALLOC * sg_list_increment);
	while ((sg_list_size + sg_list_increment) <= max_list_size
	   &&  (sg_list_size % PAGE_SIZE) != 0) {
		bus_size_t new_mod;
		bus_size_t best_mod;

		sg_list_size += sg_list_increment;
		new_mod = sg_list_size % PAGE_SIZE;
		best_mod = best_list_size % PAGE_SIZE;
		if (new_mod > best_mod || new_mod == 0) {
			best_list_size = sg_list_size;
		}
	}
	return (best_list_size);
}