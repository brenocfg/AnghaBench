#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct nvme_tcp_queue {TYPE_3__* ctrl; } ;
struct blk_mq_tags {int dummy; } ;
struct TYPE_5__ {struct blk_mq_tags** tags; } ;
struct TYPE_4__ {struct blk_mq_tags** tags; } ;
struct TYPE_6__ {TYPE_2__ tag_set; TYPE_1__ admin_tag_set; } ;

/* Variables and functions */
 size_t nvme_tcp_queue_id (struct nvme_tcp_queue*) ; 

__attribute__((used)) static inline struct blk_mq_tags *nvme_tcp_tagset(struct nvme_tcp_queue *queue)
{
	u32 queue_idx = nvme_tcp_queue_id(queue);

	if (queue_idx == 0)
		return queue->ctrl->admin_tag_set.tags[queue_idx];
	return queue->ctrl->tag_set.tags[queue_idx - 1];
}