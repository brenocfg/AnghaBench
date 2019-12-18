#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct wf_sensor {int dummy; } ;
struct smu_cpu_power_sensor {int /*<<< orphan*/  quadratic; TYPE_3__* volts; scalar_t__ fake_volts; TYPE_4__* amps; } ;
typedef  int s32 ;
struct TYPE_10__ {int* power_quads; } ;
struct TYPE_9__ {TYPE_1__* ops; } ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_7__ {int (* get_value ) (TYPE_3__*,int*) ;} ;
struct TYPE_6__ {int (* get_value ) (TYPE_4__*,int*) ;} ;

/* Variables and functions */
 TYPE_5__* cpuvcp ; 
 int stub1 (TYPE_4__*,int*) ; 
 int stub2 (TYPE_3__*,int*) ; 
 struct smu_cpu_power_sensor* to_smu_cpu_power (struct wf_sensor*) ; 

__attribute__((used)) static int smu_cpu_power_get(struct wf_sensor *sr, s32 *value)
{
	struct smu_cpu_power_sensor *pow = to_smu_cpu_power(sr);
	s32 volts, amps, power;
	u64 tmps, tmpa, tmpb;
	int rc;

	rc = pow->amps->ops->get_value(pow->amps, &amps);
	if (rc)
		return rc;

	if (pow->fake_volts) {
		*value = amps * 12 - 0x30000;
		return 0;
	}

	rc = pow->volts->ops->get_value(pow->volts, &volts);
	if (rc)
		return rc;

	power = (s32)((((u64)volts) * ((u64)amps)) >> 16);
	if (!pow->quadratic) {
		*value = power;
		return 0;
	}
	tmps = (((u64)power) * ((u64)power)) >> 16;
	tmpa = ((u64)cpuvcp->power_quads[0]) * tmps;
	tmpb = ((u64)cpuvcp->power_quads[1]) * ((u64)power);
	*value = (tmpa >> 28) + (tmpb >> 28) + (cpuvcp->power_quads[2] >> 12);

	return 0;
}