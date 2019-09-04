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
struct videobuf_queue {struct via_camera* priv_data; } ;
struct videobuf_buffer {int /*<<< orphan*/  state; } ;
struct via_camera {TYPE_1__* platdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 int /*<<< orphan*/  videobuf_dma_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videobuf_dma_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videobuf_to_dma (struct videobuf_buffer*) ; 

__attribute__((used)) static void viacam_vb_buf_release(struct videobuf_queue *q,
		struct videobuf_buffer *vb)
{
	struct via_camera *cam = q->priv_data;

	videobuf_dma_unmap(&cam->platdev->dev, videobuf_to_dma(vb));
	videobuf_dma_free(videobuf_to_dma(vb));
	vb->state = VIDEOBUF_NEEDS_INIT;
}