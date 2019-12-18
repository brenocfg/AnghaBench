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
struct hantro_dev {int /*<<< orphan*/  watchdog_work; int /*<<< orphan*/  m2m_dev; } ;
struct hantro_ctx {int dummy; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;

/* Variables and functions */
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hantro_job_finish (struct hantro_dev*,struct hantro_ctx*,unsigned int,int) ; 
 struct hantro_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 

void hantro_irq_done(struct hantro_dev *vpu, unsigned int bytesused,
		     enum vb2_buffer_state result)
{
	struct hantro_ctx *ctx =
		v4l2_m2m_get_curr_priv(vpu->m2m_dev);

	/*
	 * If cancel_delayed_work returns false
	 * the timeout expired. The watchdog is running,
	 * and will take care of finishing the job.
	 */
	if (cancel_delayed_work(&vpu->watchdog_work))
		hantro_job_finish(vpu, ctx, bytesused, result);
}