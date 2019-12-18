#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ms5611_state {int (* read_prom_word ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;TYPE_1__* chip_info; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * prom; } ;

/* Variables and functions */
 int ENODEV ; 
 int MS5611_PROM_WORDS_NB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct ms5611_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ms5611_prom_is_valid (int /*<<< orphan*/ *,int) ; 
 int stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ms5611_read_prom(struct iio_dev *indio_dev)
{
	int ret, i;
	struct ms5611_state *st = iio_priv(indio_dev);

	for (i = 0; i < MS5611_PROM_WORDS_NB; i++) {
		ret = st->read_prom_word(&indio_dev->dev,
					 i, &st->chip_info->prom[i]);
		if (ret < 0) {
			dev_err(&indio_dev->dev,
				"failed to read prom at %d\n", i);
			return ret;
		}
	}

	if (!ms5611_prom_is_valid(st->chip_info->prom, MS5611_PROM_WORDS_NB)) {
		dev_err(&indio_dev->dev, "PROM integrity check failed\n");
		return -ENODEV;
	}

	return 0;
}