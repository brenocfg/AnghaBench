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
struct task_struct {int dummy; } ;
struct ina2xx_chip_info {unsigned int allow_async_readout; struct task_struct* task; int /*<<< orphan*/  avg; } ;
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; scalar_t__* active_scan_mask; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 unsigned int SAMPLING_PERIOD (struct ina2xx_chip_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,...) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 struct ina2xx_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ina2xx_capture_thread ; 
 struct task_struct* kthread_create (int /*<<< orphan*/ ,void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static int ina2xx_buffer_enable(struct iio_dev *indio_dev)
{
	struct ina2xx_chip_info *chip = iio_priv(indio_dev);
	unsigned int sampling_us = SAMPLING_PERIOD(chip);
	struct task_struct *task;

	dev_dbg(&indio_dev->dev, "Enabling buffer w/ scan_mask %02x, freq = %d, avg =%u\n",
		(unsigned int)(*indio_dev->active_scan_mask),
		1000000 / sampling_us, chip->avg);

	dev_dbg(&indio_dev->dev, "Expected work period: %u us\n", sampling_us);
	dev_dbg(&indio_dev->dev, "Async readout mode: %d\n",
		chip->allow_async_readout);

	task = kthread_create(ina2xx_capture_thread, (void *)indio_dev,
			      "%s:%d-%uus", indio_dev->name, indio_dev->id,
			      sampling_us);
	if (IS_ERR(task))
		return PTR_ERR(task);

	get_task_struct(task);
	wake_up_process(task);
	chip->task = task;

	return 0;
}