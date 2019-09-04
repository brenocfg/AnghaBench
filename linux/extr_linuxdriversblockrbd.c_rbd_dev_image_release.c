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
struct rbd_device {TYPE_1__* spec; scalar_t__ image_format; scalar_t__ opts; } ;
struct TYPE_2__ {int /*<<< orphan*/ * image_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_dev_unprobe (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_unregister_watch (struct rbd_device*) ; 

__attribute__((used)) static void rbd_dev_image_release(struct rbd_device *rbd_dev)
{
	rbd_dev_unprobe(rbd_dev);
	if (rbd_dev->opts)
		rbd_unregister_watch(rbd_dev);
	rbd_dev->image_format = 0;
	kfree(rbd_dev->spec->image_id);
	rbd_dev->spec->image_id = NULL;
}