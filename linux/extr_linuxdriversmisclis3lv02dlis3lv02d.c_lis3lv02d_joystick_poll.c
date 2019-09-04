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
struct lis3lv02d {int /*<<< orphan*/  mutex; } ;
struct input_polled_dev {int /*<<< orphan*/  input; struct lis3lv02d* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lis3lv02d_get_xyz (struct lis3lv02d*,int*,int*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lis3lv02d_joystick_poll(struct input_polled_dev *pidev)
{
	struct lis3lv02d *lis3 = pidev->private;
	int x, y, z;

	mutex_lock(&lis3->mutex);
	lis3lv02d_get_xyz(lis3, &x, &y, &z);
	input_report_abs(pidev->input, ABS_X, x);
	input_report_abs(pidev->input, ABS_Y, y);
	input_report_abs(pidev->input, ABS_Z, z);
	input_sync(pidev->input);
	mutex_unlock(&lis3->mutex);
}