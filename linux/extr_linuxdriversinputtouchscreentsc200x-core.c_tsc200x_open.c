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
struct tsc200x {int opened; int /*<<< orphan*/  mutex; int /*<<< orphan*/  suspended; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tsc200x_enable (struct tsc200x*) ; 
 struct tsc200x* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tsc200x_open(struct input_dev *input)
{
	struct tsc200x *ts = input_get_drvdata(input);

	mutex_lock(&ts->mutex);

	if (!ts->suspended)
		__tsc200x_enable(ts);

	ts->opened = true;

	mutex_unlock(&ts->mutex);

	return 0;
}