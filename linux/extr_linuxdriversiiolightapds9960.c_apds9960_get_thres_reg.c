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
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int /*<<< orphan*/  APDS9960_REG_AIHTL ; 
 int /*<<< orphan*/  APDS9960_REG_AILTL ; 
 int /*<<< orphan*/  APDS9960_REG_PIHT ; 
 int /*<<< orphan*/  APDS9960_REG_PILT ; 
 int EINVAL ; 
#define  IIO_EV_DIR_FALLING 131 
#define  IIO_EV_DIR_RISING 130 
#define  IIO_INTENSITY 129 
#define  IIO_PROXIMITY 128 

__attribute__((used)) static inline int apds9960_get_thres_reg(const struct iio_chan_spec *chan,
					 enum iio_event_direction dir,
					 u8 *reg)
{
	switch (dir) {
	case IIO_EV_DIR_RISING:
		switch (chan->type) {
		case IIO_PROXIMITY:
			*reg = APDS9960_REG_PIHT;
			break;
		case IIO_INTENSITY:
			*reg = APDS9960_REG_AIHTL;
			break;
		default:
			return -EINVAL;
		}
		break;
	case IIO_EV_DIR_FALLING:
		switch (chan->type) {
		case IIO_PROXIMITY:
			*reg = APDS9960_REG_PILT;
			break;
		case IIO_INTENSITY:
			*reg = APDS9960_REG_AILTL;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}