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
struct skd_device {TYPE_2__* pdev; } ;
struct request {TYPE_1__* q; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct skd_device* queuedata; } ;

/* Variables and functions */
 int BLK_EH_RESET_TIMER ; 
 int /*<<< orphan*/  blk_mq_unique_tag (struct request*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum blk_eh_timer_return skd_timed_out(struct request *req,
					      bool reserved)
{
	struct skd_device *skdev = req->q->queuedata;

	dev_err(&skdev->pdev->dev, "request with tag %#x timed out\n",
		blk_mq_unique_tag(req));

	return BLK_EH_RESET_TIMER;
}