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
struct camss_video {int /*<<< orphan*/  vb2_q; } ;

/* Variables and functions */
 scalar_t__ vb2_is_streaming (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 

void msm_video_stop_streaming(struct camss_video *video)
{
	if (vb2_is_streaming(&video->vb2_q))
		vb2_queue_release(&video->vb2_q);
}