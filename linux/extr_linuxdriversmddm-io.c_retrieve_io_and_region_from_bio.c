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
struct io {int dummy; } ;
struct bio {scalar_t__ bi_private; } ;

/* Variables and functions */
 int DM_IO_MAX_REGIONS ; 

__attribute__((used)) static void retrieve_io_and_region_from_bio(struct bio *bio, struct io **io,
				       unsigned *region)
{
	unsigned long val = (unsigned long)bio->bi_private;

	*io = (void *)(val & -(unsigned long)DM_IO_MAX_REGIONS);
	*region = val & (DM_IO_MAX_REGIONS - 1);
}