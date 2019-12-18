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
typedef  int /*<<< orphan*/  u16 ;
struct ad7606_state {int /*<<< orphan*/  dev; TYPE_2__* bops; scalar_t__ gpio_frstdata; int /*<<< orphan*/ * data; TYPE_1__* chip_info; } ;
struct TYPE_4__ {int (* read_block ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {unsigned int num_channels; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ad7606_reset (struct ad7606_state*) ; 
 int /*<<< orphan*/  gpiod_get_value (scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7606_read_samples(struct ad7606_state *st)
{
	unsigned int num = st->chip_info->num_channels;
	u16 *data = st->data;
	int ret;

	/*
	 * The frstdata signal is set to high while and after reading the sample
	 * of the first channel and low for all other channels. This can be used
	 * to check that the incoming data is correctly aligned. During normal
	 * operation the data should never become unaligned, but some glitch or
	 * electrostatic discharge might cause an extra read or clock cycle.
	 * Monitoring the frstdata signal allows to recover from such failure
	 * situations.
	 */

	if (st->gpio_frstdata) {
		ret = st->bops->read_block(st->dev, 1, data);
		if (ret)
			return ret;

		if (!gpiod_get_value(st->gpio_frstdata)) {
			ad7606_reset(st);
			return -EIO;
		}

		data++;
		num--;
	}

	return st->bops->read_block(st->dev, num, data);
}