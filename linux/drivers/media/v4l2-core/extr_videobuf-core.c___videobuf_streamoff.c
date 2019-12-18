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
struct videobuf_queue {int /*<<< orphan*/  streaming; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  videobuf_queue_cancel (struct videobuf_queue*) ; 

__attribute__((used)) static int __videobuf_streamoff(struct videobuf_queue *q)
{
	if (!q->streaming)
		return -EINVAL;

	videobuf_queue_cancel(q);

	return 0;
}