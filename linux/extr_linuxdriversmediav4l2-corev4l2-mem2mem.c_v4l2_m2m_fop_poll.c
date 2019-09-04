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
struct v4l2_m2m_ctx {scalar_t__ q_lock; } ;
struct v4l2_fh {struct v4l2_m2m_ctx* m2m_ctx; } ;
struct file {struct v4l2_fh* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (scalar_t__) ; 
 int /*<<< orphan*/  v4l2_m2m_poll (struct file*,struct v4l2_m2m_ctx*,int /*<<< orphan*/ *) ; 

__poll_t v4l2_m2m_fop_poll(struct file *file, poll_table *wait)
{
	struct v4l2_fh *fh = file->private_data;
	struct v4l2_m2m_ctx *m2m_ctx = fh->m2m_ctx;
	__poll_t ret;

	if (m2m_ctx->q_lock)
		mutex_lock(m2m_ctx->q_lock);

	ret = v4l2_m2m_poll(file, m2m_ctx, wait);

	if (m2m_ctx->q_lock)
		mutex_unlock(m2m_ctx->q_lock);

	return ret;
}