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
struct joydev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  handle; int /*<<< orphan*/  open; scalar_t__ exist; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_close_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void joydev_close_device(struct joydev *joydev)
{
	mutex_lock(&joydev->mutex);

	if (joydev->exist && !--joydev->open)
		input_close_device(&joydev->handle);

	mutex_unlock(&joydev->mutex);
}