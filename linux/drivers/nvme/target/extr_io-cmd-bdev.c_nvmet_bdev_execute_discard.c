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
typedef  scalar_t__ u16 ;
struct nvmet_req {TYPE_2__* cmd; } ;
struct nvme_dsm_range {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_status; int /*<<< orphan*/  bi_end_io; struct nvmet_req* bi_private; } ;
typedef  int /*<<< orphan*/  range ;
struct TYPE_3__ {int /*<<< orphan*/  nr; } ;
struct TYPE_4__ {TYPE_1__ dsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_bdev_discard_range (struct nvmet_req*,struct nvme_dsm_range*,struct bio**) ; 
 int /*<<< orphan*/  nvmet_bio_done ; 
 scalar_t__ nvmet_copy_from_sgl (struct nvmet_req*,int,struct nvme_dsm_range*,int) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,scalar_t__) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static void nvmet_bdev_execute_discard(struct nvmet_req *req)
{
	struct nvme_dsm_range range;
	struct bio *bio = NULL;
	int i;
	u16 status;

	for (i = 0; i <= le32_to_cpu(req->cmd->dsm.nr); i++) {
		status = nvmet_copy_from_sgl(req, i * sizeof(range), &range,
				sizeof(range));
		if (status)
			break;

		status = nvmet_bdev_discard_range(req, &range, &bio);
		if (status)
			break;
	}

	if (bio) {
		bio->bi_private = req;
		bio->bi_end_io = nvmet_bio_done;
		if (status) {
			bio->bi_status = BLK_STS_IOERR;
			bio_endio(bio);
		} else {
			submit_bio(bio);
		}
	} else {
		nvmet_req_complete(req, status);
	}
}