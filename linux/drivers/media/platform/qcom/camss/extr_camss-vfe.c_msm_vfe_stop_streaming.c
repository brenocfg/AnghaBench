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
struct vfe_device {TYPE_1__* line; } ;
struct TYPE_2__ {int /*<<< orphan*/  video_out; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  msm_video_stop_streaming (int /*<<< orphan*/ *) ; 

void msm_vfe_stop_streaming(struct vfe_device *vfe)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(vfe->line); i++)
		msm_video_stop_streaming(&vfe->line[i].video_out);
}