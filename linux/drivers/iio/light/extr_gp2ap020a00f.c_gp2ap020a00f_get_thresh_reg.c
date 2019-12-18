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
typedef  int /*<<< orphan*/  u8 ;
struct iio_chan_spec {int type; } ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GP2AP020A00F_PH_L_REG ; 
 int /*<<< orphan*/  GP2AP020A00F_PL_L_REG ; 
 int /*<<< orphan*/  GP2AP020A00F_TH_L_REG ; 
 int /*<<< orphan*/  GP2AP020A00F_TL_L_REG ; 
 int IIO_EV_DIR_RISING ; 
#define  IIO_LIGHT 129 
#define  IIO_PROXIMITY 128 

__attribute__((used)) static u8 gp2ap020a00f_get_thresh_reg(const struct iio_chan_spec *chan,
					     enum iio_event_direction event_dir)
{
	switch (chan->type) {
	case IIO_PROXIMITY:
		if (event_dir == IIO_EV_DIR_RISING)
			return GP2AP020A00F_PH_L_REG;
		else
			return GP2AP020A00F_PL_L_REG;
	case IIO_LIGHT:
		if (event_dir == IIO_EV_DIR_RISING)
			return GP2AP020A00F_TH_L_REG;
		else
			return GP2AP020A00F_TL_L_REG;
	default:
		break;
	}

	return -EINVAL;
}