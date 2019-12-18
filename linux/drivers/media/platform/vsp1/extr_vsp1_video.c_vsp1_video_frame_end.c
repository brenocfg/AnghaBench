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
struct vsp1_video {int pipe_index; TYPE_1__* rwpf; } ;
struct vsp1_vb2_buffer {int /*<<< orphan*/  mem; } ;
struct vsp1_rwpf {struct vsp1_video* video; } ;
struct vsp1_pipeline {int buffers_ready; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 struct vsp1_vb2_buffer* vsp1_video_complete_buffer (struct vsp1_video*) ; 

__attribute__((used)) static void vsp1_video_frame_end(struct vsp1_pipeline *pipe,
				 struct vsp1_rwpf *rwpf)
{
	struct vsp1_video *video = rwpf->video;
	struct vsp1_vb2_buffer *buf;

	buf = vsp1_video_complete_buffer(video);
	if (buf == NULL)
		return;

	video->rwpf->mem = buf->mem;
	pipe->buffers_ready |= 1 << video->pipe_index;
}