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
struct mpu3050 {int /*<<< orphan*/  dev; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct mpu3050* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpu3050_buffer_postdisable(struct iio_dev *indio_dev)
{
	struct mpu3050 *mpu3050 = iio_priv(indio_dev);

	pm_runtime_mark_last_busy(mpu3050->dev);
	pm_runtime_put_autosuspend(mpu3050->dev);

	return 0;
}