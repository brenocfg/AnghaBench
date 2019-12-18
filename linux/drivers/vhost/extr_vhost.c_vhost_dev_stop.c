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
struct vhost_dev {int nvqs; TYPE_1__** vqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  poll; scalar_t__ handle_kick; scalar_t__ kick; } ;

/* Variables and functions */
 int /*<<< orphan*/  vhost_poll_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_poll_stop (int /*<<< orphan*/ *) ; 

void vhost_dev_stop(struct vhost_dev *dev)
{
	int i;

	for (i = 0; i < dev->nvqs; ++i) {
		if (dev->vqs[i]->kick && dev->vqs[i]->handle_kick) {
			vhost_poll_stop(&dev->vqs[i]->poll);
			vhost_poll_flush(&dev->vqs[i]->poll);
		}
	}
}