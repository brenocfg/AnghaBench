#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pipe; } ;
struct media_entity {int dummy; } ;
struct TYPE_3__ {struct media_entity entity; } ;
struct vimc_cap_device {int /*<<< orphan*/  ved; TYPE_2__ stream; scalar_t__ sequence; TYPE_1__ vdev; } ;
struct vb2_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int media_pipeline_start (struct media_entity*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (struct media_entity*) ; 
 struct vimc_cap_device* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vimc_cap_return_all_buffers (struct vimc_cap_device*,int /*<<< orphan*/ ) ; 
 int vimc_streamer_s_stream (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vimc_cap_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct vimc_cap_device *vcap = vb2_get_drv_priv(vq);
	struct media_entity *entity = &vcap->vdev.entity;
	int ret;

	vcap->sequence = 0;

	/* Start the media pipeline */
	ret = media_pipeline_start(entity, &vcap->stream.pipe);
	if (ret) {
		vimc_cap_return_all_buffers(vcap, VB2_BUF_STATE_QUEUED);
		return ret;
	}

	ret = vimc_streamer_s_stream(&vcap->stream, &vcap->ved, 1);
	if (ret) {
		media_pipeline_stop(entity);
		vimc_cap_return_all_buffers(vcap, VB2_BUF_STATE_QUEUED);
		return ret;
	}

	return 0;
}