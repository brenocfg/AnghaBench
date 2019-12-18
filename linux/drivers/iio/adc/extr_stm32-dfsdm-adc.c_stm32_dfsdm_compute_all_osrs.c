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
struct stm32_dfsdm_filter {int /*<<< orphan*/ * flo; } ;
struct stm32_dfsdm_adc {size_t fl_id; TYPE_1__* dfsdm; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct stm32_dfsdm_filter* fl_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stm32_dfsdm_compute_osrs (struct stm32_dfsdm_filter*,int,unsigned int) ; 

__attribute__((used)) static int stm32_dfsdm_compute_all_osrs(struct iio_dev *indio_dev,
					unsigned int oversamp)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	struct stm32_dfsdm_filter *fl = &adc->dfsdm->fl_list[adc->fl_id];
	int ret0, ret1;

	memset(&fl->flo[0], 0, sizeof(fl->flo[0]));
	memset(&fl->flo[1], 0, sizeof(fl->flo[1]));

	ret0 = stm32_dfsdm_compute_osrs(fl, 0, oversamp);
	ret1 = stm32_dfsdm_compute_osrs(fl, 1, oversamp);
	if (ret0 < 0 && ret1 < 0) {
		dev_err(&indio_dev->dev,
			"Filter parameters not found: errors %d/%d\n",
			ret0, ret1);
		return -EINVAL;
	}

	return 0;
}