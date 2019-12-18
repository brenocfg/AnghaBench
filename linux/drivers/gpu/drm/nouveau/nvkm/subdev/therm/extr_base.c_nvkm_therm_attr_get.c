#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int temp; int hysteresis; } ;
struct TYPE_10__ {int temp; int hysteresis; } ;
struct TYPE_9__ {int temp; int hysteresis; } ;
struct TYPE_8__ {int temp; int hysteresis; } ;
struct TYPE_12__ {TYPE_4__ thrs_shutdown; TYPE_3__ thrs_critical; TYPE_2__ thrs_down_clock; TYPE_1__ thrs_fan_boost; } ;
struct nvkm_therm {int mode; TYPE_5__ bios_sensor; TYPE_7__* fan; } ;
typedef  enum nvkm_therm_attr_type { ____Placeholder_nvkm_therm_attr_type } nvkm_therm_attr_type ;
struct TYPE_13__ {int min_duty; int max_duty; } ;
struct TYPE_14__ {TYPE_6__ bios; } ;

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

int
nvkm_therm_attr_get(struct nvkm_therm *therm, enum nvkm_therm_attr_type type)
{
	switch (type) {
	case NVKM_THERM_ATTR_FAN_MIN_DUTY:
		return therm->fan->bios.min_duty;
	case NVKM_THERM_ATTR_FAN_MAX_DUTY:
		return therm->fan->bios.max_duty;
	case NVKM_THERM_ATTR_FAN_MODE:
		return therm->mode;
	case NVKM_THERM_ATTR_THRS_FAN_BOOST:
		return therm->bios_sensor.thrs_fan_boost.temp;
	case NVKM_THERM_ATTR_THRS_FAN_BOOST_HYST:
		return therm->bios_sensor.thrs_fan_boost.hysteresis;
	case NVKM_THERM_ATTR_THRS_DOWN_CLK:
		return therm->bios_sensor.thrs_down_clock.temp;
	case NVKM_THERM_ATTR_THRS_DOWN_CLK_HYST:
		return therm->bios_sensor.thrs_down_clock.hysteresis;
	case NVKM_THERM_ATTR_THRS_CRITICAL:
		return therm->bios_sensor.thrs_critical.temp;
	case NVKM_THERM_ATTR_THRS_CRITICAL_HYST:
		return therm->bios_sensor.thrs_critical.hysteresis;
	case NVKM_THERM_ATTR_THRS_SHUTDOWN:
		return therm->bios_sensor.thrs_shutdown.temp;
	case NVKM_THERM_ATTR_THRS_SHUTDOWN_HYST:
		return therm->bios_sensor.thrs_shutdown.hysteresis;
	}

	return -EINVAL;
}