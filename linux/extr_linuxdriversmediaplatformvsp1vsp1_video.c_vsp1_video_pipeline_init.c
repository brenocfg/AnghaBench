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
struct vsp1_video {int dummy; } ;
struct vsp1_pipeline {int /*<<< orphan*/  frame_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  vsp1_pipeline_init (struct vsp1_pipeline*) ; 
 int vsp1_video_pipeline_build (struct vsp1_pipeline*,struct vsp1_video*) ; 
 int /*<<< orphan*/  vsp1_video_pipeline_frame_end ; 

__attribute__((used)) static int vsp1_video_pipeline_init(struct vsp1_pipeline *pipe,
				    struct vsp1_video *video)
{
	vsp1_pipeline_init(pipe);

	pipe->frame_end = vsp1_video_pipeline_frame_end;

	return vsp1_video_pipeline_build(pipe, video);
}