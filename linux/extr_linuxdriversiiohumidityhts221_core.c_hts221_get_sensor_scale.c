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
struct hts221_hw {TYPE_1__* sensors; } ;
typedef  int s64 ;
typedef  long long s32 ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;
struct TYPE_2__ {long long slope; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t HTS221_SENSOR_H ; 
 size_t HTS221_SENSOR_T ; 
#define  IIO_HUMIDITYRELATIVE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT_PLUS_NANO ; 
 int div_s64 (long long,long long) ; 
 int div_s64_rem (int,long long,long long*) ; 

__attribute__((used)) static int hts221_get_sensor_scale(struct hts221_hw *hw,
				   enum iio_chan_type ch_type,
				   int *val, int *val2)
{
	s64 tmp;
	s32 rem, div, data;

	switch (ch_type) {
	case IIO_HUMIDITYRELATIVE:
		data = hw->sensors[HTS221_SENSOR_H].slope;
		div = (1 << 4) * 1000;
		break;
	case IIO_TEMP:
		data = hw->sensors[HTS221_SENSOR_T].slope;
		div = (1 << 6) * 1000;
		break;
	default:
		return -EINVAL;
	}

	tmp = div_s64(data * 1000000000LL, div);
	tmp = div_s64_rem(tmp, 1000000000LL, &rem);

	*val = tmp;
	*val2 = rem;

	return IIO_VAL_INT_PLUS_NANO;
}