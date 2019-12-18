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
typedef  int /*<<< orphan*/  u16 ;
struct pmbus_sensor {size_t class; } ;
struct pmbus_data {TYPE_1__* info; } ;
typedef  int s64 ;
typedef  int s32 ;
struct TYPE_2__ {int* m; int* b; int* R; } ;

/* Variables and functions */
 size_t PSC_FAN ; 
 size_t PSC_POWER ; 
 size_t PSC_PWM ; 
 int /*<<< orphan*/  S16_MAX ; 
 int /*<<< orphan*/  S16_MIN ; 
 int /*<<< orphan*/  clamp_val (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int div_s64 (int,long) ; 

__attribute__((used)) static u16 pmbus_data2reg_direct(struct pmbus_data *data,
				 struct pmbus_sensor *sensor, long val)
{
	s64 b, val64 = val;
	s32 m, R;

	m = data->info->m[sensor->class];
	b = data->info->b[sensor->class];
	R = data->info->R[sensor->class];

	/* Power is in uW. Adjust R and b. */
	if (sensor->class == PSC_POWER) {
		R -= 3;
		b *= 1000;
	}

	/* Calculate Y = (m * X + b) * 10^R */
	if (!(sensor->class == PSC_FAN || sensor->class == PSC_PWM)) {
		R -= 3;		/* Adjust R and b for data in milli-units */
		b *= 1000;
	}
	val64 = val64 * m + b;

	while (R > 0) {
		val64 *= 10;
		R--;
	}
	while (R < 0) {
		val64 = div_s64(val64 + 5LL, 10L);  /* round closest */
		R++;
	}

	return (u16)clamp_val(val64, S16_MIN, S16_MAX);
}