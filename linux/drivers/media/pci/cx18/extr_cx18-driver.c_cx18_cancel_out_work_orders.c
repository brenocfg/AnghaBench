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
struct cx18 {TYPE_2__* streams; } ;
struct TYPE_3__ {scalar_t__ v4l2_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  out_work_order; TYPE_1__ video_dev; } ;

/* Variables and functions */
 int CX18_MAX_STREAMS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx18_cancel_out_work_orders(struct cx18 *cx)
{
	int i;
	for (i = 0; i < CX18_MAX_STREAMS; i++)
		if (cx->streams[i].video_dev.v4l2_dev)
			cancel_work_sync(&cx->streams[i].out_work_order);
}