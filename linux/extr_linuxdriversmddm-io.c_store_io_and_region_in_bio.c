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
struct bio {void* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DMCRIT (char*,struct io*) ; 
 int /*<<< orphan*/  DM_IO_MAX_REGIONS ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void store_io_and_region_in_bio(struct bio *bio, struct io *io,
				       unsigned region)
{
	if (unlikely(!IS_ALIGNED((unsigned long)io, DM_IO_MAX_REGIONS))) {
		DMCRIT("Unaligned struct io pointer %p", io);
		BUG();
	}

	bio->bi_private = (void *)((unsigned long)io | region);
}