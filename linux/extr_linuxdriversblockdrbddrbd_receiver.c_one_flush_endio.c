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
struct one_flush_context {struct issue_flush_context* ctx; struct drbd_device* device; } ;
struct issue_flush_context {int /*<<< orphan*/  done; int /*<<< orphan*/  pending; int /*<<< orphan*/  error; } ;
struct drbd_device {int /*<<< orphan*/  kref; int /*<<< orphan*/  flags; } ;
struct bio {scalar_t__ bi_status; struct one_flush_context* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_PENDING ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_destroy_device ; 
 int /*<<< orphan*/  drbd_info (struct drbd_device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct one_flush_context*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 

__attribute__((used)) static void one_flush_endio(struct bio *bio)
{
	struct one_flush_context *octx = bio->bi_private;
	struct drbd_device *device = octx->device;
	struct issue_flush_context *ctx = octx->ctx;

	if (bio->bi_status) {
		ctx->error = blk_status_to_errno(bio->bi_status);
		drbd_info(device, "local disk FLUSH FAILED with status %d\n", bio->bi_status);
	}
	kfree(octx);
	bio_put(bio);

	clear_bit(FLUSH_PENDING, &device->flags);
	put_ldev(device);
	kref_put(&device->kref, drbd_destroy_device);

	if (atomic_dec_and_test(&ctx->pending))
		complete(&ctx->done);
}