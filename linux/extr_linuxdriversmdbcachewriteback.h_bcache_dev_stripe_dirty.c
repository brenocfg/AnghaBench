#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {unsigned int stripe_size; scalar_t__ stripe_sectors_dirty; } ;
struct cached_dev {TYPE_1__ disk; } ;

/* Variables and functions */
 scalar_t__ atomic_read (scalar_t__) ; 
 unsigned int offset_to_stripe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool bcache_dev_stripe_dirty(struct cached_dev *dc,
					   uint64_t offset,
					   unsigned int nr_sectors)
{
	unsigned int stripe = offset_to_stripe(&dc->disk, offset);

	while (1) {
		if (atomic_read(dc->disk.stripe_sectors_dirty + stripe))
			return true;

		if (nr_sectors <= dc->disk.stripe_size)
			return false;

		nr_sectors -= dc->disk.stripe_size;
		stripe++;
	}
}