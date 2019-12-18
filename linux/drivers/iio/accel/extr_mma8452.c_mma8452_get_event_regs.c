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
struct mma8452_event_regs {int dummy; } ;
struct mma8452_data {TYPE_1__* chip_info; } ;
struct iio_chan_spec {int type; } ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
struct TYPE_2__ {int all_events; int enabled_events; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACCEL 130 
#define  IIO_EV_DIR_FALLING 129 
#define  IIO_EV_DIR_RISING 128 
 int MMA8452_INT_TRANS ; 
 struct mma8452_event_regs ff_mt_ev_regs ; 
 struct mma8452_event_regs trans_ev_regs ; 

__attribute__((used)) static int mma8452_get_event_regs(struct mma8452_data *data,
		const struct iio_chan_spec *chan, enum iio_event_direction dir,
		const struct mma8452_event_regs **ev_reg)
{
	if (!chan)
		return -EINVAL;

	switch (chan->type) {
	case IIO_ACCEL:
		switch (dir) {
		case IIO_EV_DIR_RISING:
			if ((data->chip_info->all_events
					& MMA8452_INT_TRANS) &&
				(data->chip_info->enabled_events
					& MMA8452_INT_TRANS))
				*ev_reg = &trans_ev_regs;
			else
				*ev_reg = &ff_mt_ev_regs;
			return 0;
		case IIO_EV_DIR_FALLING:
			*ev_reg = &ff_mt_ev_regs;
			return 0;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}