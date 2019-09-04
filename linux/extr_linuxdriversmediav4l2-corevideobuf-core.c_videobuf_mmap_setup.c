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
struct videobuf_queue {int dummy; } ;
typedef  enum v4l2_memory { ____Placeholder_v4l2_memory } v4l2_memory ;

/* Variables and functions */
 int __videobuf_mmap_setup (struct videobuf_queue*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  videobuf_queue_lock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_queue_unlock (struct videobuf_queue*) ; 

int videobuf_mmap_setup(struct videobuf_queue *q,
			unsigned int bcount, unsigned int bsize,
			enum v4l2_memory memory)
{
	int ret;
	videobuf_queue_lock(q);
	ret = __videobuf_mmap_setup(q, bcount, bsize, memory);
	videobuf_queue_unlock(q);
	return ret;
}