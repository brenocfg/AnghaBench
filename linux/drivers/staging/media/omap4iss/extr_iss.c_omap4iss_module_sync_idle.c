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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct media_entity {int dummy; } ;
struct iss_video {int dmaqueue_flags; int /*<<< orphan*/  qlock; } ;
struct iss_pipeline {scalar_t__ stream_state; struct iss_video* output; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ ISS_PIPELINE_STREAM_SINGLESHOT ; 
 scalar_t__ ISS_PIPELINE_STREAM_STOPPED ; 
 int ISS_VIDEO_DMAQUEUE_UNDERRUN ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iss_pipeline_is_last (struct media_entity*) ; 
 int /*<<< orphan*/  iss_pipeline_ready (struct iss_pipeline*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct iss_pipeline* to_iss_pipeline (struct media_entity*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int omap4iss_module_sync_idle(struct media_entity *me, wait_queue_head_t *wait,
			      atomic_t *stopping)
{
	struct iss_pipeline *pipe = to_iss_pipeline(me);
	struct iss_video *video = pipe->output;
	unsigned long flags;

	if (pipe->stream_state == ISS_PIPELINE_STREAM_STOPPED ||
	    (pipe->stream_state == ISS_PIPELINE_STREAM_SINGLESHOT &&
	     !iss_pipeline_ready(pipe)))
		return 0;

	/*
	 * atomic_set() doesn't include memory barrier on ARM platform for SMP
	 * scenario. We'll call it here to avoid race conditions.
	 */
	atomic_set(stopping, 1);
	smp_wmb();

	/*
	 * If module is the last one, it's writing to memory. In this case,
	 * it's necessary to check if the module is already paused due to
	 * DMA queue underrun or if it has to wait for next interrupt to be
	 * idle.
	 * If it isn't the last one, the function won't sleep but *stopping
	 * will still be set to warn next submodule caller's interrupt the
	 * module wants to be idle.
	 */
	if (!iss_pipeline_is_last(me))
		return 0;

	spin_lock_irqsave(&video->qlock, flags);
	if (video->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_UNDERRUN) {
		spin_unlock_irqrestore(&video->qlock, flags);
		atomic_set(stopping, 0);
		smp_wmb();
		return 0;
	}
	spin_unlock_irqrestore(&video->qlock, flags);
	if (!wait_event_timeout(*wait, !atomic_read(stopping),
				msecs_to_jiffies(1000))) {
		atomic_set(stopping, 0);
		smp_wmb();
		return -ETIMEDOUT;
	}

	return 0;
}