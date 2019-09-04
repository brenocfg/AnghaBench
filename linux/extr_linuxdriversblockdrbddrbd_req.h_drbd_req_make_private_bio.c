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
struct drbd_request {struct bio* private_bio; } ;
struct bio {int /*<<< orphan*/ * bi_next; int /*<<< orphan*/  bi_end_io; struct drbd_request* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 struct bio* bio_clone_fast (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_io_bio_set ; 
 int /*<<< orphan*/  drbd_request_endio ; 

__attribute__((used)) static inline void drbd_req_make_private_bio(struct drbd_request *req, struct bio *bio_src)
{
	struct bio *bio;
	bio = bio_clone_fast(bio_src, GFP_NOIO, &drbd_io_bio_set);

	req->private_bio = bio;

	bio->bi_private  = req;
	bio->bi_end_io   = drbd_request_endio;
	bio->bi_next     = NULL;
}