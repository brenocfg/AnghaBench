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
struct dmz_bioctx {struct dm_zone* zone; int /*<<< orphan*/  ref; } ;
struct dm_zone {int /*<<< orphan*/  flags; } ;
struct bio {scalar_t__ bi_status; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 scalar_t__ BLK_STS_OK ; 
 int /*<<< orphan*/  DMZ_SEQ_WRITE_ERR ; 
 scalar_t__ REQ_OP_WRITE ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 struct dmz_bioctx* dm_per_bio_data (struct bio*,int) ; 
 int /*<<< orphan*/  dmz_deactivate_zone (struct dm_zone*) ; 
 scalar_t__ dmz_is_seq (struct dm_zone*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dmz_bio_endio(struct bio *bio, blk_status_t status)
{
	struct dmz_bioctx *bioctx = dm_per_bio_data(bio, sizeof(struct dmz_bioctx));

	if (status != BLK_STS_OK && bio->bi_status == BLK_STS_OK)
		bio->bi_status = status;

	if (refcount_dec_and_test(&bioctx->ref)) {
		struct dm_zone *zone = bioctx->zone;

		if (zone) {
			if (bio->bi_status != BLK_STS_OK &&
			    bio_op(bio) == REQ_OP_WRITE &&
			    dmz_is_seq(zone))
				set_bit(DMZ_SEQ_WRITE_ERR, &zone->flags);
			dmz_deactivate_zone(zone);
		}
		bio_endio(bio);
	}
}