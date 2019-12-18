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
struct TYPE_3__ {int /*<<< orphan*/ * tagset; } ;
struct TYPE_4__ {scalar_t__ tags; } ;
struct nvme_dev {TYPE_1__ ctrl; TYPE_2__ tagset; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_tag_set (TYPE_2__*) ; 

__attribute__((used)) static void nvme_free_tagset(struct nvme_dev *dev)
{
	if (dev->tagset.tags)
		blk_mq_free_tag_set(&dev->tagset);
	dev->ctrl.tagset = NULL;
}