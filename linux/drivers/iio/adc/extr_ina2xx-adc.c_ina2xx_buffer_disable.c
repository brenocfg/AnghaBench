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
struct ina2xx_chip_info {int /*<<< orphan*/ * task; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct ina2xx_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ina2xx_buffer_disable(struct iio_dev *indio_dev)
{
	struct ina2xx_chip_info *chip = iio_priv(indio_dev);

	if (chip->task) {
		kthread_stop(chip->task);
		put_task_struct(chip->task);
		chip->task = NULL;
	}

	return 0;
}