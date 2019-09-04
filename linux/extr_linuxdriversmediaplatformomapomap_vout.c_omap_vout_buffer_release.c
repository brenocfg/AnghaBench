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
struct videobuf_buffer {scalar_t__ memory; struct frame_vector* priv; int /*<<< orphan*/  state; } ;
struct frame_vector {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_MEMORY_USERPTR ; 
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 int /*<<< orphan*/  frame_vector_destroy (struct frame_vector*) ; 
 int /*<<< orphan*/  put_vaddr_frames (struct frame_vector*) ; 

__attribute__((used)) static void omap_vout_buffer_release(struct videobuf_queue *q,
			    struct videobuf_buffer *vb)
{
	vb->state = VIDEOBUF_NEEDS_INIT;
	if (vb->memory == V4L2_MEMORY_USERPTR && vb->priv) {
		struct frame_vector *vec = vb->priv;

		put_vaddr_frames(vec);
		frame_vector_destroy(vec);
	}
}