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
struct uvc_video_queue {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 unsigned long vb2_get_unmapped_area (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

unsigned long uvc_queue_get_unmapped_area(struct uvc_video_queue *queue,
		unsigned long pgoff)
{
	return vb2_get_unmapped_area(&queue->queue, 0, 0, pgoff, 0);
}