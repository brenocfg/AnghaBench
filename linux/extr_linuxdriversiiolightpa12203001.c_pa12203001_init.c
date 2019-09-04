#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pa12203001_data {int /*<<< orphan*/  map; } ;
struct iio_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 struct pa12203001_data* iio_priv (struct iio_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* regvals ; 

__attribute__((used)) static int pa12203001_init(struct iio_dev *indio_dev)
{
	struct pa12203001_data *data = iio_priv(indio_dev);
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(regvals); i++) {
		ret = regmap_write(data->map, regvals[i].reg, regvals[i].val);
		if (ret < 0)
			return ret;
	}

	return 0;
}