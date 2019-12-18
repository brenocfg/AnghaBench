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
struct amvdec_session {int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/  m2m_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdec_m2m_job_abort(void *priv)
{
	struct amvdec_session *sess = priv;

	v4l2_m2m_job_finish(sess->m2m_dev, sess->m2m_ctx);
}