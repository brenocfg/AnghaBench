#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int /*<<< orphan*/  channels; } ;
struct ad7606_state {unsigned long* oversampling_avail; TYPE_1__* bops; int /*<<< orphan*/ * write_os; int /*<<< orphan*/  write_scale; int /*<<< orphan*/  num_os_ratios; TYPE_2__* gpio_os; } ;
struct TYPE_4__ {int /*<<< orphan*/  info; int /*<<< orphan*/  desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reg_write ) (struct ad7606_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AD7606_CONFIGURATION_REGISTER ; 
 int /*<<< orphan*/  AD7606_SINGLE_DOUT ; 
 int /*<<< orphan*/  ARRAY_SIZE (unsigned long*) ; 
 unsigned long* ad7606B_oversampling_avail ; 
 int /*<<< orphan*/  ad7606_write_os_sw ; 
 int /*<<< orphan*/  ad7606_write_scale_sw ; 
 int /*<<< orphan*/  ad7606b_sw_channels ; 
 int /*<<< orphan*/  gpiod_set_array_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  stub1 (struct ad7606_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7606B_sw_mode_config(struct iio_dev *indio_dev)
{
	struct ad7606_state *st = iio_priv(indio_dev);
	unsigned long os[3] = {1};

	/*
	 * Software mode is enabled when all three oversampling
	 * pins are set to high. If oversampling gpios are defined
	 * in the device tree, then they need to be set to high,
	 * otherwise, they must be hardwired to VDD
	 */
	if (st->gpio_os) {
		gpiod_set_array_value(ARRAY_SIZE(os),
				      st->gpio_os->desc, st->gpio_os->info, os);
	}
	/* OS of 128 and 256 are available only in software mode */
	st->oversampling_avail = ad7606B_oversampling_avail;
	st->num_os_ratios = ARRAY_SIZE(ad7606B_oversampling_avail);

	st->write_scale = ad7606_write_scale_sw;
	st->write_os = &ad7606_write_os_sw;

	/* Configure device spi to output on a single channel */
	st->bops->reg_write(st,
			    AD7606_CONFIGURATION_REGISTER,
			    AD7606_SINGLE_DOUT);

	/*
	 * Scale can be configured individually for each channel
	 * in software mode.
	 */
	indio_dev->channels = ad7606b_sw_channels;

	return 0;
}