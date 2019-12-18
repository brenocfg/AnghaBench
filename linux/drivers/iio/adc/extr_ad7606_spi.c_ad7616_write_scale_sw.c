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
struct iio_dev {int dummy; } ;
struct ad7606_state {TYPE_1__* bops; } ;
struct TYPE_2__ {int (* write_mask ) (struct ad7606_state*,unsigned int,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 unsigned int AD7616_RANGE_CH_ADDR (unsigned int) ; 
 scalar_t__ AD7616_RANGE_CH_A_ADDR_OFF ; 
 scalar_t__ AD7616_RANGE_CH_B_ADDR_OFF ; 
 unsigned int AD7616_RANGE_CH_MODE (unsigned int,int) ; 
 int /*<<< orphan*/  AD7616_RANGE_CH_MSK (unsigned int) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 
 int stub1 (struct ad7606_state*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ad7616_write_scale_sw(struct iio_dev *indio_dev, int ch, int val)
{
	struct ad7606_state *st = iio_priv(indio_dev);
	unsigned int ch_addr, mode, ch_index;


	/*
	 * Ad7616 has 16 channels divided in group A and group B.
	 * The range of channels from A are stored in registers with address 4
	 * while channels from B are stored in register with address 6.
	 * The last bit from channels determines if it is from group A or B
	 * because the order of channels in iio is 0A, 0B, 1A, 1B...
	 */
	ch_index = ch >> 1;

	ch_addr = AD7616_RANGE_CH_ADDR(ch_index);

	if ((ch & 0x1) == 0) /* channel A */
		ch_addr += AD7616_RANGE_CH_A_ADDR_OFF;
	else	/* channel B */
		ch_addr += AD7616_RANGE_CH_B_ADDR_OFF;

	/* 0b01 for 2.5v, 0b10 for 5v and 0b11 for 10v */
	mode = AD7616_RANGE_CH_MODE(ch_index, ((val + 1) & 0b11));
	return st->bops->write_mask(st, ch_addr, AD7616_RANGE_CH_MSK(ch_index),
				     mode);
}