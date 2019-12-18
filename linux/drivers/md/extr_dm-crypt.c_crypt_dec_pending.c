#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  req; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct dm_crypt_io {int /*<<< orphan*/  integrity_metadata; struct crypt_config* cc; int /*<<< orphan*/  integrity_metadata_from_pool; TYPE_2__ ctx; int /*<<< orphan*/  io_pending; int /*<<< orphan*/  error; struct bio* base_bio; } ;
struct crypt_config {int /*<<< orphan*/  tag_pool; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  crypt_free_req (struct crypt_config*,int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypt_dec_pending(struct dm_crypt_io *io)
{
	struct crypt_config *cc = io->cc;
	struct bio *base_bio = io->base_bio;
	blk_status_t error = io->error;

	if (!atomic_dec_and_test(&io->io_pending))
		return;

	if (io->ctx.r.req)
		crypt_free_req(cc, io->ctx.r.req, base_bio);

	if (unlikely(io->integrity_metadata_from_pool))
		mempool_free(io->integrity_metadata, &io->cc->tag_pool);
	else
		kfree(io->integrity_metadata);

	base_bio->bi_status = error;
	bio_endio(base_bio);
}