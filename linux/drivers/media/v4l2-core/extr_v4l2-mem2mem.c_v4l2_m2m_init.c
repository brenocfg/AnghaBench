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
struct v4l2_m2m_ops {int /*<<< orphan*/  device_run; } ;
struct v4l2_m2m_dev {int /*<<< orphan*/  job_work; int /*<<< orphan*/  job_spinlock; int /*<<< orphan*/  job_queue; struct v4l2_m2m_ops const* m2m_ops; int /*<<< orphan*/ * curr_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct v4l2_m2m_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct v4l2_m2m_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_device_run_work ; 

struct v4l2_m2m_dev *v4l2_m2m_init(const struct v4l2_m2m_ops *m2m_ops)
{
	struct v4l2_m2m_dev *m2m_dev;

	if (!m2m_ops || WARN_ON(!m2m_ops->device_run))
		return ERR_PTR(-EINVAL);

	m2m_dev = kzalloc(sizeof *m2m_dev, GFP_KERNEL);
	if (!m2m_dev)
		return ERR_PTR(-ENOMEM);

	m2m_dev->curr_ctx = NULL;
	m2m_dev->m2m_ops = m2m_ops;
	INIT_LIST_HEAD(&m2m_dev->job_queue);
	spin_lock_init(&m2m_dev->job_spinlock);
	INIT_WORK(&m2m_dev->job_work, v4l2_m2m_device_run_work);

	return m2m_dev;
}