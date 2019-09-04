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
struct pmbus_sensor {size_t class; int /*<<< orphan*/  data; } ;
struct pmbus_data {TYPE_1__* info; } ;
typedef  int s64 ;
typedef  int s32 ;
typedef  int s16 ;
struct TYPE_2__ {int* m; int* b; int* R; } ;

/* Variables and functions */
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  LONG_MIN ; 
 size_t PSC_FAN ; 
 size_t PSC_POWER ; 
 size_t PSC_PWM ; 
 long clamp_val (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int div_s64 (int,int) ; 

__attribute__((used)) static long pmbus_reg2data_direct(struct pmbus_data *data,
				  struct pmbus_sensor *sensor)
{
	s64 b, val = (s16)sensor->data;
	s32 m, R;

	m = data->info->m[sensor->class];
	b = data->info->b[sensor->class];
	R = data->info->R[sensor->class];

	if (m == 0)
		return 0;

	/* X = 1/m * (Y * 10^-R - b) */
	R = -R;
	/* scale result to milli-units for everything but fans */
	if (!(sensor->class == PSC_FAN || sensor->class == PSC_PWM)) {
		R += 3;
		b *= 1000;
	}

	/* scale result to micro-units for power sensors */
	if (sensor->class == PSC_POWER) {
		R += 3;
		b *= 1000;
	}

	while (R > 0) {
		val *= 10;
		R--;
	}
	while (R < 0) {
		val = div_s64(val + 5LL, 10L);  /* round closest */
		R++;
	}

	val = div_s64(val - b, m);
	return clamp_val(val, LONG_MIN, LONG_MAX);
}