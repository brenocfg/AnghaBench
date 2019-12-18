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
struct input_dev {int dummy; } ;
struct adxl34x {int opened; int /*<<< orphan*/  mutex; int /*<<< orphan*/  disabled; int /*<<< orphan*/  suspended; } ;

/* Variables and functions */
 int /*<<< orphan*/  __adxl34x_disable (struct adxl34x*) ; 
 struct adxl34x* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adxl34x_input_close(struct input_dev *input)
{
	struct adxl34x *ac = input_get_drvdata(input);

	mutex_lock(&ac->mutex);

	if (!ac->suspended && !ac->disabled)
		__adxl34x_disable(ac);

	ac->opened = false;

	mutex_unlock(&ac->mutex);
}