#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dm_snapshot {int /*<<< orphan*/  kcopyd_client; TYPE_1__* store; TYPE_2__* cow; } ;
struct dm_io_region {int /*<<< orphan*/  count; int /*<<< orphan*/  sector; int /*<<< orphan*/  bdev; } ;
struct dm_exception {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {struct dm_snapshot* bi_private; TYPE_3__ bi_iter; } ;
typedef  int /*<<< orphan*/  chunk_t ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  chunk_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (struct dm_snapshot*) ; 
 int /*<<< orphan*/  account_start_copy (struct dm_snapshot*) ; 
 int /*<<< orphan*/  dm_kcopyd_zero (int /*<<< orphan*/ ,int,struct dm_io_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  zero_callback ; 

__attribute__((used)) static void zero_exception(struct dm_snapshot *s, struct dm_exception *e,
			   struct bio *bio, chunk_t chunk)
{
	struct dm_io_region dest;

	dest.bdev = s->cow->bdev;
	dest.sector = bio->bi_iter.bi_sector;
	dest.count = s->store->chunk_size;

	account_start_copy(s);
	WARN_ON_ONCE(bio->bi_private);
	bio->bi_private = s;
	dm_kcopyd_zero(s->kcopyd_client, 1, &dest, 0, zero_callback, bio);
}