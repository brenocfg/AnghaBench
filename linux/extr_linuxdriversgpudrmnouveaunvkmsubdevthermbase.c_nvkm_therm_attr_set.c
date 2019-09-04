#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int temp; int hysteresis; } ;
struct TYPE_13__ {int temp; int hysteresis; } ;
struct TYPE_12__ {int temp; int hysteresis; } ;
struct TYPE_11__ {int temp; int hysteresis; } ;
struct TYPE_15__ {TYPE_6__ thrs_shutdown; TYPE_5__ thrs_critical; TYPE_4__ thrs_down_clock; TYPE_3__ thrs_fan_boost; } ;
struct nvkm_therm {TYPE_8__* func; TYPE_7__ bios_sensor; TYPE_2__* fan; } ;
typedef  enum nvkm_therm_attr_type { ____Placeholder_nvkm_therm_attr_type } nvkm_therm_attr_type ;
struct TYPE_16__ {int /*<<< orphan*/  (* program_alarms ) (struct nvkm_therm*) ;} ;
struct TYPE_9__ {int max_duty; int min_duty; } ;
struct TYPE_10__ {TYPE_1__ bios; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVKM_THERM_ATTR_FAN_MAX_DUTY 138 
#define  NVKM_THERM_ATTR_FAN_MIN_DUTY 137 
#define  NVKM_THERM_ATTR_FAN_MODE 136 
#define  NVKM_THERM_ATTR_THRS_CRITICAL 135 
#define  NVKM_THERM_ATTR_THRS_CRITICAL_HYST 134 
#define  NVKM_THERM_ATTR_THRS_DOWN_CLK 133 
#define  NVKM_THERM_ATTR_THRS_DOWN_CLK_HYST 132 
#define  NVKM_THERM_ATTR_THRS_FAN_BOOST 131 
#define  NVKM_THERM_ATTR_THRS_FAN_BOOST_HYST 130 
#define  NVKM_THERM_ATTR_THRS_SHUTDOWN 129 
#define  NVKM_THERM_ATTR_THRS_SHUTDOWN_HYST 128 
 int nvkm_therm_fan_mode (struct nvkm_therm*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_therm*) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_therm*) ; 
 int /*<<< orphan*/  stub3 (struct nvkm_therm*) ; 
 int /*<<< orphan*/  stub4 (struct nvkm_therm*) ; 
 int /*<<< orphan*/  stub5 (struct nvkm_therm*) ; 
 int /*<<< orphan*/  stub6 (struct nvkm_therm*) ; 
 int /*<<< orphan*/  stub7 (struct nvkm_therm*) ; 
 int /*<<< orphan*/  stub8 (struct nvkm_therm*) ; 

int
nvkm_therm_attr_set(struct nvkm_therm *therm,
		    enum nvkm_therm_attr_type type, int value)
{
	switch (type) {
	case NVKM_THERM_ATTR_FAN_MIN_DUTY:
		if (value < 0)
			value = 0;
		if (value > therm->fan->bios.max_duty)
			value = therm->fan->bios.max_duty;
		therm->fan->bios.min_duty = value;
		return 0;
	case NVKM_THERM_ATTR_FAN_MAX_DUTY:
		if (value < 0)
			value = 0;
		if (value < therm->fan->bios.min_duty)
			value = therm->fan->bios.min_duty;
		therm->fan->bios.max_duty = value;
		return 0;
	case NVKM_THERM_ATTR_FAN_MODE:
		return nvkm_therm_fan_mode(therm, value);
	case NVKM_THERM_ATTR_THRS_FAN_BOOST:
		therm->bios_sensor.thrs_fan_boost.temp = value;
		therm->func->program_alarms(therm);
		return 0;
	case NVKM_THERM_ATTR_THRS_FAN_BOOST_HYST:
		therm->bios_sensor.thrs_fan_boost.hysteresis = value;
		therm->func->program_alarms(therm);
		return 0;
	case NVKM_THERM_ATTR_THRS_DOWN_CLK:
		therm->bios_sensor.thrs_down_clock.temp = value;
		therm->func->program_alarms(therm);
		return 0;
	case NVKM_THERM_ATTR_THRS_DOWN_CLK_HYST:
		therm->bios_sensor.thrs_down_clock.hysteresis = value;
		therm->func->program_alarms(therm);
		return 0;
	case NVKM_THERM_ATTR_THRS_CRITICAL:
		therm->bios_sensor.thrs_critical.temp = value;
		therm->func->program_alarms(therm);
		return 0;
	case NVKM_THERM_ATTR_THRS_CRITICAL_HYST:
		therm->bios_sensor.thrs_critical.hysteresis = value;
		therm->func->program_alarms(therm);
		return 0;
	case NVKM_THERM_ATTR_THRS_SHUTDOWN:
		therm->bios_sensor.thrs_shutdown.temp = value;
		therm->func->program_alarms(therm);
		return 0;
	case NVKM_THERM_ATTR_THRS_SHUTDOWN_HYST:
		therm->bios_sensor.thrs_shutdown.hysteresis = value;
		therm->func->program_alarms(therm);
		return 0;
	}

	return -EINVAL;
}