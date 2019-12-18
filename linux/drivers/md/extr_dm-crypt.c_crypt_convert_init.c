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
struct crypt_config {scalar_t__ iv_offset; } ;
struct convert_context {int /*<<< orphan*/  restart; scalar_t__ cc_sector; int /*<<< orphan*/  iter_out; int /*<<< orphan*/  iter_in; struct bio* bio_out; struct bio* bio_in; } ;
struct bio {int /*<<< orphan*/  bi_iter; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypt_convert_init(struct crypt_config *cc,
			       struct convert_context *ctx,
			       struct bio *bio_out, struct bio *bio_in,
			       sector_t sector)
{
	ctx->bio_in = bio_in;
	ctx->bio_out = bio_out;
	if (bio_in)
		ctx->iter_in = bio_in->bi_iter;
	if (bio_out)
		ctx->iter_out = bio_out->bi_iter;
	ctx->cc_sector = sector + cc->iv_offset;
	init_completion(&ctx->restart);
}