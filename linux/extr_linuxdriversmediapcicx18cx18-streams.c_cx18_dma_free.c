#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct cx18_videobuf_buffer {TYPE_1__ vb; } ;
struct cx18_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 int /*<<< orphan*/  videobuf_vmalloc_free (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_waiton (struct videobuf_queue*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx18_dma_free(struct videobuf_queue *q,
	struct cx18_stream *s, struct cx18_videobuf_buffer *buf)
{
	videobuf_waiton(q, &buf->vb, 0, 0);
	videobuf_vmalloc_free(&buf->vb);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
}