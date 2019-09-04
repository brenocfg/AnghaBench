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
struct zpa2326_private {int result; int /*<<< orphan*/  regmap; int /*<<< orphan*/  data_ready; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int ETIME ; 
 int /*<<< orphan*/  ZPA2326_CONVERSION_JIFFIES ; 
 int /*<<< orphan*/  ZPA2326_INT_SOURCE_REG ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpa2326_dbg (struct iio_dev const*,char*) ; 
 int /*<<< orphan*/  zpa2326_warn (struct iio_dev const*,char*,...) ; 

__attribute__((used)) static int zpa2326_wait_oneshot_completion(const struct iio_dev   *indio_dev,
					   struct zpa2326_private *private)
{
	unsigned int val;
	long     timeout;

	zpa2326_dbg(indio_dev, "waiting for one shot completion interrupt");

	timeout = wait_for_completion_interruptible_timeout(
		&private->data_ready, ZPA2326_CONVERSION_JIFFIES);
	if (timeout > 0)
		/*
		 * Interrupt handler completed before timeout: return operation
		 * status.
		 */
		return private->result;

	/* Clear all interrupts just to be sure. */
	regmap_read(private->regmap, ZPA2326_INT_SOURCE_REG, &val);

	if (!timeout) {
		/* Timed out. */
		zpa2326_warn(indio_dev, "no one shot interrupt occurred (%ld)",
			     timeout);
		return -ETIME;
	}

	zpa2326_warn(indio_dev, "wait for one shot interrupt cancelled");
	return -ERESTARTSYS;
}