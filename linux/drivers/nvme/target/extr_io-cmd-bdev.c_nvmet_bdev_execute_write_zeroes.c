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
struct nvmet_req {TYPE_2__* ns; TYPE_1__* cmd; } ;
struct nvme_write_zeroes_cmd {int /*<<< orphan*/  length; int /*<<< orphan*/  slba; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct nvmet_req* bi_private; } ;
typedef  int sector_t ;
struct TYPE_4__ {int blksize_shift; int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {struct nvme_write_zeroes_cmd write_zeroes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __blkdev_issue_zeroout (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct bio**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno_to_nvme_status (struct nvmet_req*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_bio_done ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static void nvmet_bdev_execute_write_zeroes(struct nvmet_req *req)
{
	struct nvme_write_zeroes_cmd *write_zeroes = &req->cmd->write_zeroes;
	struct bio *bio = NULL;
	sector_t sector;
	sector_t nr_sector;
	int ret;

	sector = le64_to_cpu(write_zeroes->slba) <<
		(req->ns->blksize_shift - 9);
	nr_sector = (((sector_t)le16_to_cpu(write_zeroes->length) + 1) <<
		(req->ns->blksize_shift - 9));

	ret = __blkdev_issue_zeroout(req->ns->bdev, sector, nr_sector,
			GFP_KERNEL, &bio, 0);
	if (bio) {
		bio->bi_private = req;
		bio->bi_end_io = nvmet_bio_done;
		submit_bio(bio);
	} else {
		nvmet_req_complete(req, errno_to_nvme_status(req, ret));
	}
}