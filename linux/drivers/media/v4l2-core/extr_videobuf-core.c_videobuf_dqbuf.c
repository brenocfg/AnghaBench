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
struct videobuf_queue {int /*<<< orphan*/  type; TYPE_1__* int_ops; } ;
struct videobuf_buffer {int state; int /*<<< orphan*/  stream; } ;
struct v4l2_buffer {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL (struct videobuf_queue*,int /*<<< orphan*/ ,struct videobuf_queue*,struct videobuf_buffer*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_QTYPE_OPS ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_DONE ; 
#define  VIDEOBUF_DONE 129 
#define  VIDEOBUF_ERROR 128 
 int VIDEOBUF_IDLE ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct v4l2_buffer*,int /*<<< orphan*/ ,int) ; 
 int stream_next_buffer (struct videobuf_queue*,struct videobuf_buffer**,int) ; 
 int /*<<< orphan*/  sync ; 
 int /*<<< orphan*/  videobuf_queue_lock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_queue_unlock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_status (struct videobuf_queue*,struct v4l2_buffer*,struct videobuf_buffer*,int /*<<< orphan*/ ) ; 

int videobuf_dqbuf(struct videobuf_queue *q,
		   struct v4l2_buffer *b, int nonblocking)
{
	struct videobuf_buffer *buf = NULL;
	int retval;

	MAGIC_CHECK(q->int_ops->magic, MAGIC_QTYPE_OPS);

	memset(b, 0, sizeof(*b));
	videobuf_queue_lock(q);

	retval = stream_next_buffer(q, &buf, nonblocking);
	if (retval < 0) {
		dprintk(1, "dqbuf: next_buffer error: %i\n", retval);
		goto done;
	}

	switch (buf->state) {
	case VIDEOBUF_ERROR:
		dprintk(1, "dqbuf: state is error\n");
		break;
	case VIDEOBUF_DONE:
		dprintk(1, "dqbuf: state is done\n");
		break;
	default:
		dprintk(1, "dqbuf: state invalid\n");
		retval = -EINVAL;
		goto done;
	}
	CALL(q, sync, q, buf);
	videobuf_status(q, b, buf, q->type);
	list_del(&buf->stream);
	buf->state = VIDEOBUF_IDLE;
	b->flags &= ~V4L2_BUF_FLAG_DONE;
done:
	videobuf_queue_unlock(q);
	return retval;
}