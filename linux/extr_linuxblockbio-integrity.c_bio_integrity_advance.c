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
struct blk_integrity {int dummy; } ;
struct TYPE_2__ {unsigned int bi_sector; } ;
struct bio_integrity_payload {TYPE_1__ bip_iter; int /*<<< orphan*/  bip_vec; } ;
struct bio {int /*<<< orphan*/  bi_disk; } ;

/* Variables and functions */
 struct bio_integrity_payload* bio_integrity (struct bio*) ; 
 unsigned int bio_integrity_bytes (struct blk_integrity*,unsigned int) ; 
 struct blk_integrity* blk_get_integrity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bvec_iter_advance (int /*<<< orphan*/ ,TYPE_1__*,unsigned int) ; 

void bio_integrity_advance(struct bio *bio, unsigned int bytes_done)
{
	struct bio_integrity_payload *bip = bio_integrity(bio);
	struct blk_integrity *bi = blk_get_integrity(bio->bi_disk);
	unsigned bytes = bio_integrity_bytes(bi, bytes_done >> 9);

	bip->bip_iter.bi_sector += bytes_done >> 9;
	bvec_iter_advance(bip->bip_vec, &bip->bip_iter, bytes);
}