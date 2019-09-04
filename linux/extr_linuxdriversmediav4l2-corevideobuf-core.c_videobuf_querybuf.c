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
struct videobuf_queue {scalar_t__ type; int /*<<< orphan*/ ** bufs; } ;
struct v4l2_buffer {scalar_t__ type; size_t index; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t VIDEO_MAX_FRAME ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  videobuf_queue_lock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_queue_unlock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_status (struct videobuf_queue*,struct v4l2_buffer*,int /*<<< orphan*/ *,scalar_t__) ; 

int videobuf_querybuf(struct videobuf_queue *q, struct v4l2_buffer *b)
{
	int ret = -EINVAL;

	videobuf_queue_lock(q);
	if (unlikely(b->type != q->type)) {
		dprintk(1, "querybuf: Wrong type.\n");
		goto done;
	}
	if (unlikely(b->index >= VIDEO_MAX_FRAME)) {
		dprintk(1, "querybuf: index out of range.\n");
		goto done;
	}
	if (unlikely(NULL == q->bufs[b->index])) {
		dprintk(1, "querybuf: buffer is null.\n");
		goto done;
	}

	videobuf_status(q, b, q->bufs[b->index], q->type);

	ret = 0;
done:
	videobuf_queue_unlock(q);
	return ret;
}