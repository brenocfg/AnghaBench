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
struct bio {int /*<<< orphan*/  bi_status; struct nvmet_req* bi_private; } ;
struct TYPE_2__ {struct bio inline_bio; } ;
struct nvmet_req {TYPE_1__ b; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_to_nvme_status (struct nvmet_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmet_bio_done(struct bio *bio)
{
	struct nvmet_req *req = bio->bi_private;

	nvmet_req_complete(req, blk_to_nvme_status(req, bio->bi_status));
	if (bio != &req->b.inline_bio)
		bio_put(bio);
}