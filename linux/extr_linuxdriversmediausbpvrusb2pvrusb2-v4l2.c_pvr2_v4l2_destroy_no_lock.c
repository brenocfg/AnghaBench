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
struct pvr2_v4l2 {int /*<<< orphan*/  channel; int /*<<< orphan*/ * dev_radio; int /*<<< orphan*/ * dev_video; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_STRUCT ; 
 int /*<<< orphan*/  kfree (struct pvr2_v4l2*) ; 
 int /*<<< orphan*/  pvr2_channel_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_v4l2*) ; 
 int /*<<< orphan*/  pvr2_v4l2_dev_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvr2_v4l2_destroy_no_lock(struct pvr2_v4l2 *vp)
{
	if (vp->dev_video) {
		pvr2_v4l2_dev_destroy(vp->dev_video);
		vp->dev_video = NULL;
	}
	if (vp->dev_radio) {
		pvr2_v4l2_dev_destroy(vp->dev_radio);
		vp->dev_radio = NULL;
	}

	pvr2_trace(PVR2_TRACE_STRUCT,"Destroying pvr2_v4l2 id=%p",vp);
	pvr2_channel_done(&vp->channel);
	kfree(vp);
}