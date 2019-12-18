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
struct host1x_job {TYPE_2__* channel; } ;
struct host1x {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct host1x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int host1x_hw_channel_submit (struct host1x*,struct host1x_job*) ; 

int host1x_job_submit(struct host1x_job *job)
{
	struct host1x *host = dev_get_drvdata(job->channel->dev->parent);

	return host1x_hw_channel_submit(host, job);
}