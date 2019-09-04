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
struct cma3000_accl_data {int opened; int /*<<< orphan*/  mutex; int /*<<< orphan*/  suspended; } ;

/* Variables and functions */
 int /*<<< orphan*/  cma3000_poweroff (struct cma3000_accl_data*) ; 
 struct cma3000_accl_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cma3000_close(struct input_dev *input_dev)
{
	struct cma3000_accl_data *data = input_get_drvdata(input_dev);

	mutex_lock(&data->mutex);

	if (!data->suspended)
		cma3000_poweroff(data);

	data->opened = false;

	mutex_unlock(&data->mutex);
}