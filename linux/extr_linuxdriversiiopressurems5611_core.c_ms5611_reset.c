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
struct ms5611_state {int (* reset ) (int /*<<< orphan*/ *) ;} ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ms5611_state* iio_priv (struct iio_dev*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ms5611_reset(struct iio_dev *indio_dev)
{
	int ret;
	struct ms5611_state *st = iio_priv(indio_dev);

	ret = st->reset(&indio_dev->dev);
	if (ret < 0) {
		dev_err(&indio_dev->dev, "failed to reset device\n");
		return ret;
	}

	usleep_range(3000, 4000);

	return 0;
}