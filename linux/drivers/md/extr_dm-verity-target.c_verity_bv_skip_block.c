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
struct dm_verity_io {int dummy; } ;
struct dm_verity {int data_dev_block_bits; TYPE_1__* ti; } ;
struct bvec_iter {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  per_io_data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_advance_iter (struct bio*,struct bvec_iter*,int) ; 
 struct bio* dm_bio_from_per_bio_data (struct dm_verity_io*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void verity_bv_skip_block(struct dm_verity *v,
					struct dm_verity_io *io,
					struct bvec_iter *iter)
{
	struct bio *bio = dm_bio_from_per_bio_data(io, v->ti->per_io_data_size);

	bio_advance_iter(bio, iter, 1 << v->data_dev_block_bits);
}