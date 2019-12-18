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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvme_ns_head {int dummy; } ;
struct nvme_ns {int /*<<< orphan*/  queue; TYPE_1__* head; } ;
struct TYPE_4__ {void* cdw10; void* nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_2__ common; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int /*<<< orphan*/  c ;
struct TYPE_3__ {int /*<<< orphan*/  ns_id; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 struct nvme_ns* nvme_get_ns_from_disk (int /*<<< orphan*/ ,struct nvme_ns_head**,int*) ; 
 int /*<<< orphan*/  nvme_put_ns_from_disk (struct nvme_ns_head*,int) ; 
 int nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvme_pr_command(struct block_device *bdev, u32 cdw10,
				u64 key, u64 sa_key, u8 op)
{
	struct nvme_ns_head *head = NULL;
	struct nvme_ns *ns;
	struct nvme_command c;
	int srcu_idx, ret;
	u8 data[16] = { 0, };

	ns = nvme_get_ns_from_disk(bdev->bd_disk, &head, &srcu_idx);
	if (unlikely(!ns))
		return -EWOULDBLOCK;

	put_unaligned_le64(key, &data[0]);
	put_unaligned_le64(sa_key, &data[8]);

	memset(&c, 0, sizeof(c));
	c.common.opcode = op;
	c.common.nsid = cpu_to_le32(ns->head->ns_id);
	c.common.cdw10 = cpu_to_le32(cdw10);

	ret = nvme_submit_sync_cmd(ns->queue, &c, data, 16);
	nvme_put_ns_from_disk(head, srcu_idx);
	return ret;
}