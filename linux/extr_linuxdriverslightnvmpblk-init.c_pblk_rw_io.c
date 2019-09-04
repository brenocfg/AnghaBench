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
struct request_queue {int dummy; } ;
struct pblk {int /*<<< orphan*/  rl; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLONED ; 
 int NVM_IO_DONE ; 
 int /*<<< orphan*/  PBLK_IOTYPE_USER ; 
 scalar_t__ READ ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_queue_split (struct request_queue*,struct bio**) ; 
 scalar_t__ pblk_get_secs (struct bio*) ; 
 scalar_t__ pblk_rl_max_io (int /*<<< orphan*/ *) ; 
 int pblk_submit_read (struct pblk*,struct bio*) ; 
 int pblk_write_to_cache (struct pblk*,struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_rw_io(struct request_queue *q, struct pblk *pblk,
			  struct bio *bio)
{
	int ret;

	/* Read requests must be <= 256kb due to NVMe's 64 bit completion bitmap
	 * constraint. Writes can be of arbitrary size.
	 */
	if (bio_data_dir(bio) == READ) {
		blk_queue_split(q, &bio);
		ret = pblk_submit_read(pblk, bio);
		if (ret == NVM_IO_DONE && bio_flagged(bio, BIO_CLONED))
			bio_put(bio);

		return ret;
	}

	/* Prevent deadlock in the case of a modest LUN configuration and large
	 * user I/Os. Unless stalled, the rate limiter leaves at least 256KB
	 * available for user I/O.
	 */
	if (pblk_get_secs(bio) > pblk_rl_max_io(&pblk->rl))
		blk_queue_split(q, &bio);

	return pblk_write_to_cache(pblk, bio, PBLK_IOTYPE_USER);
}