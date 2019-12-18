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
struct zpa2326_private {struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZPA2326_PRESS_OUT_H_REG ; 
 unsigned int ZPA2326_STATUS_FIFO_E ; 
 int /*<<< orphan*/  ZPA2326_STATUS_REG ; 
 scalar_t__ iio_priv (struct iio_dev const*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  zpa2326_dbg (struct iio_dev const*,char*) ; 
 int /*<<< orphan*/  zpa2326_err (struct iio_dev const*,char*,int) ; 

__attribute__((used)) static int zpa2326_clear_fifo(const struct iio_dev *indio_dev,
			      unsigned int          min_count)
{
	struct regmap *regs = ((struct zpa2326_private *)
			       iio_priv(indio_dev))->regmap;
	int            err;
	unsigned int   val;

	if (!min_count) {
		/*
		 * No hint: read status register to determine whether FIFO is
		 * empty or not.
		 */
		err = regmap_read(regs, ZPA2326_STATUS_REG, &val);

		if (err < 0)
			goto err;

		if (val & ZPA2326_STATUS_FIFO_E)
			/* Fifo is empty: nothing to trash. */
			return 0;
	}

	/* Clear FIFO. */
	do {
		/*
		 * A single fetch from pressure MSB register is enough to pop
		 * values out of FIFO.
		 */
		err = regmap_read(regs, ZPA2326_PRESS_OUT_H_REG, &val);
		if (err < 0)
			goto err;

		if (min_count) {
			/*
			 * We know for sure there are at least min_count entries
			 * left in FIFO. Skip status register read.
			 */
			min_count--;
			continue;
		}

		err = regmap_read(regs, ZPA2326_STATUS_REG, &val);
		if (err < 0)
			goto err;

	} while (!(val & ZPA2326_STATUS_FIFO_E));

	zpa2326_dbg(indio_dev, "FIFO cleared");

	return 0;

err:
	zpa2326_err(indio_dev, "failed to clear FIFO (%d)", err);

	return err;
}