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
struct lis3lv02d {scalar_t__ pm_dev; int /*<<< orphan*/  wake_thread; } ;
struct input_polled_dev {struct lis3lv02d* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (scalar_t__) ; 

__attribute__((used)) static void lis3lv02d_joystick_close(struct input_polled_dev *pidev)
{
	struct lis3lv02d *lis3 = pidev->private;

	atomic_set(&lis3->wake_thread, 0);
	if (lis3->pm_dev)
		pm_runtime_put(lis3->pm_dev);
}