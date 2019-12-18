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
struct tape_device {int /*<<< orphan*/ * nt; TYPE_1__* cdev; int /*<<< orphan*/ * rt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_tape_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
tapechar_cleanup_device(struct tape_device *device)
{
	unregister_tape_dev(&device->cdev->dev, device->rt);
	device->rt = NULL;
	unregister_tape_dev(&device->cdev->dev, device->nt);
	device->nt = NULL;
}