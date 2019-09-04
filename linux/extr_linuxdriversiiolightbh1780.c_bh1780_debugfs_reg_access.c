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
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev {int dummy; } ;
struct bh1780_data {int dummy; } ;

/* Variables and functions */
 int bh1780_read (struct bh1780_data*,int /*<<< orphan*/ ) ; 
 int bh1780_write (struct bh1780_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bh1780_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int bh1780_debugfs_reg_access(struct iio_dev *indio_dev,
			      unsigned int reg, unsigned int writeval,
			      unsigned int *readval)
{
	struct bh1780_data *bh1780 = iio_priv(indio_dev);
	int ret;

	if (!readval)
		return bh1780_write(bh1780, (u8)reg, (u8)writeval);

	ret = bh1780_read(bh1780, (u8)reg);
	if (ret < 0)
		return ret;

	*readval = ret;

	return 0;
}