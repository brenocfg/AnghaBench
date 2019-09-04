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
struct sec_queue {TYPE_1__* dev_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int sec_queue_free (struct sec_queue*) ; 
 int /*<<< orphan*/  sec_queue_stop (struct sec_queue*) ; 

int sec_queue_stop_release(struct sec_queue *queue)
{
	struct device *dev = queue->dev_info->dev;
	int ret;

	sec_queue_stop(queue);

	ret = sec_queue_free(queue);
	if (ret)
		dev_err(dev, "Releasing queue failed %d\n", ret);

	return ret;
}