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
struct vhost_work {int dummy; } ;
struct vhost_flush_struct {int /*<<< orphan*/  wait_event; int /*<<< orphan*/  work; } ;
struct vhost_dev {scalar_t__ worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_flush_work ; 
 int /*<<< orphan*/  vhost_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_work_queue (struct vhost_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void vhost_work_flush(struct vhost_dev *dev, struct vhost_work *work)
{
	struct vhost_flush_struct flush;

	if (dev->worker) {
		init_completion(&flush.wait_event);
		vhost_work_init(&flush.work, vhost_flush_work);

		vhost_work_queue(dev, &flush.work);
		wait_for_completion(&flush.wait_event);
	}
}