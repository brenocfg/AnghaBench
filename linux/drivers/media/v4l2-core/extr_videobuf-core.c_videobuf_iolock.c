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
struct videobuf_queue {TYPE_1__* int_ops; } ;
struct videobuf_buffer {int /*<<< orphan*/  magic; } ;
struct v4l2_framebuffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int CALL (struct videobuf_queue*,int /*<<< orphan*/ ,struct videobuf_queue*,struct videobuf_buffer*,struct v4l2_framebuffer*) ; 
 int /*<<< orphan*/  MAGIC_BUFFER ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_QTYPE_OPS ; 
 int /*<<< orphan*/  iolock ; 

int videobuf_iolock(struct videobuf_queue *q, struct videobuf_buffer *vb,
		    struct v4l2_framebuffer *fbuf)
{
	MAGIC_CHECK(vb->magic, MAGIC_BUFFER);
	MAGIC_CHECK(q->int_ops->magic, MAGIC_QTYPE_OPS);

	return CALL(q, iolock, q, vb, fbuf);
}