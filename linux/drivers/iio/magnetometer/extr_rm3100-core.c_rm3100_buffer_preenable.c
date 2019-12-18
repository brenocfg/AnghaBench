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
struct rm3100_data {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int* active_scan_mask; } ;

/* Variables and functions */
 int RM3100_CMM_AXIS_SHIFT ; 
 int RM3100_CMM_START ; 
 int /*<<< orphan*/  RM3100_REG_CMM ; 
 struct rm3100_data* iio_priv (struct iio_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rm3100_buffer_preenable(struct iio_dev *indio_dev)
{
	struct rm3100_data *data = iio_priv(indio_dev);

	/* Starting channels enabled. */
	return regmap_write(data->regmap, RM3100_REG_CMM,
		(*indio_dev->active_scan_mask & 0x7) << RM3100_CMM_AXIS_SHIFT |
		RM3100_CMM_START);
}