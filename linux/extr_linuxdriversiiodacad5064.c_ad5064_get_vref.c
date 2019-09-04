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
struct iio_chan_spec {unsigned int channel; } ;
struct ad5064_state {TYPE_2__* vref_reg; TYPE_1__* chip_info; scalar_t__ use_internal_vref; } ;
struct TYPE_4__ {int /*<<< orphan*/  consumer; } ;
struct TYPE_3__ {int internal_vref; scalar_t__ shared_vref; } ;

/* Variables and functions */
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5064_get_vref(struct ad5064_state *st,
	struct iio_chan_spec const *chan)
{
	unsigned int i;

	if (st->use_internal_vref)
		return st->chip_info->internal_vref;

	i = st->chip_info->shared_vref ? 0 : chan->channel;
	return regulator_get_voltage(st->vref_reg[i].consumer);
}