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
struct v4l2_m2m_dev {int dummy; } ;
struct v4l2_m2m_ctx {struct v4l2_m2m_dev* m2m_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __v4l2_m2m_try_queue (struct v4l2_m2m_dev*,struct v4l2_m2m_ctx*) ; 
 int /*<<< orphan*/  v4l2_m2m_try_run (struct v4l2_m2m_dev*) ; 

void v4l2_m2m_try_schedule(struct v4l2_m2m_ctx *m2m_ctx)
{
	struct v4l2_m2m_dev *m2m_dev = m2m_ctx->m2m_dev;

	__v4l2_m2m_try_queue(m2m_dev, m2m_ctx);
	v4l2_m2m_try_run(m2m_dev);
}