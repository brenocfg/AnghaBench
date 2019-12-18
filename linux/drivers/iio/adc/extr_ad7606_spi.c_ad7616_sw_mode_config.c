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
struct iio_dev {int /*<<< orphan*/  channels; } ;
struct ad7606_state {TYPE_1__* bops; int /*<<< orphan*/ * write_os; int /*<<< orphan*/  write_scale; } ;
struct TYPE_2__ {int (* write_mask ) (struct ad7606_state*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int AD7616_BURST_MODE ; 
 int /*<<< orphan*/  AD7616_CONFIGURATION_REGISTER ; 
 int AD7616_SEQEN_MODE ; 
 int /*<<< orphan*/  ad7616_sw_channels ; 
 int /*<<< orphan*/  ad7616_write_os_sw ; 
 int /*<<< orphan*/  ad7616_write_scale_sw ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 
 int stub1 (struct ad7606_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ad7616_sw_mode_config(struct iio_dev *indio_dev)
{
	struct ad7606_state *st = iio_priv(indio_dev);

	/*
	 * Scale can be configured individually for each channel
	 * in software mode.
	 */
	indio_dev->channels = ad7616_sw_channels;

	st->write_scale = ad7616_write_scale_sw;
	st->write_os = &ad7616_write_os_sw;

	/* Activate Burst mode and SEQEN MODE */
	return st->bops->write_mask(st,
			      AD7616_CONFIGURATION_REGISTER,
			      AD7616_BURST_MODE | AD7616_SEQEN_MODE,
			      AD7616_BURST_MODE | AD7616_SEQEN_MODE);
}