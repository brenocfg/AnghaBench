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
typedef  int /*<<< orphan*/  u16 ;
struct nvmet_req {int error_slba; struct nvmet_ns* ns; } ;
struct nvmet_ns {int blksize_shift; int /*<<< orphan*/  bdev; } ;
struct nvme_dsm_range {int /*<<< orphan*/  slba; int /*<<< orphan*/  nlb; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_SC_SUCCESS ; 
 int __blkdev_issue_discard (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio**) ; 
 int /*<<< orphan*/  errno_to_nvme_status (struct nvmet_req*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 nvmet_bdev_discard_range(struct nvmet_req *req,
		struct nvme_dsm_range *range, struct bio **bio)
{
	struct nvmet_ns *ns = req->ns;
	int ret;

	ret = __blkdev_issue_discard(ns->bdev,
			le64_to_cpu(range->slba) << (ns->blksize_shift - 9),
			le32_to_cpu(range->nlb) << (ns->blksize_shift - 9),
			GFP_KERNEL, 0, bio);
	if (ret && ret != -EOPNOTSUPP) {
		req->error_slba = le64_to_cpu(range->slba);
		return errno_to_nvme_status(req, ret);
	}
	return NVME_SC_SUCCESS;
}