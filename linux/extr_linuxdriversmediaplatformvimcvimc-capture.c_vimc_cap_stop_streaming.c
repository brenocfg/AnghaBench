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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct vimc_cap_device {TYPE_1__ vdev; int /*<<< orphan*/  ved; int /*<<< orphan*/  stream; } ;
struct vb2_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  media_pipeline_stop (int /*<<< orphan*/ *) ; 
 struct vimc_cap_device* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vimc_cap_return_all_buffers (struct vimc_cap_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vimc_streamer_s_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vimc_cap_stop_streaming(struct vb2_queue *vq)
{
	struct vimc_cap_device *vcap = vb2_get_drv_priv(vq);

	vimc_streamer_s_stream(&vcap->stream, &vcap->ved, 0);

	/* Stop the media pipeline */
	media_pipeline_stop(&vcap->vdev.entity);

	/* Release all active buffers */
	vimc_cap_return_all_buffers(vcap, VB2_BUF_STATE_ERROR);
}