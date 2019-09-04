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
struct wf_fcu_priv {int rpm_shift; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct wf_fcu_fan {int min; int max; TYPE_1__ ctrl; struct wf_fcu_priv* fcu_priv; } ;
struct mpu_data {scalar_t__ rmaxn_intake_fan; scalar_t__ rminn_intake_fan; scalar_t__ rmaxn_exhaust_fan; scalar_t__ rminn_exhaust_fan; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int,int) ; 
 void* max (int,int /*<<< orphan*/ ) ; 
 void* min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 struct mpu_data* wf_get_mpu (int) ; 

__attribute__((used)) static void wf_fcu_get_rpmfan_minmax(struct wf_fcu_fan *fan)
{
	struct wf_fcu_priv *pv = fan->fcu_priv;
	const struct mpu_data *mpu0 = wf_get_mpu(0);
	const struct mpu_data *mpu1 = wf_get_mpu(1);

	/* Default */
	fan->min = 2400 >> pv->rpm_shift;
	fan->max = 56000 >> pv->rpm_shift;

	/* CPU fans have min/max in MPU */
	if (mpu0 && !strcmp(fan->ctrl.name, "cpu-front-fan-0")) {
		fan->min = max(fan->min, (s32)mpu0->rminn_intake_fan);
		fan->max = min(fan->max, (s32)mpu0->rmaxn_intake_fan);
		goto bail;
	}
	if (mpu1 && !strcmp(fan->ctrl.name, "cpu-front-fan-1")) {
		fan->min = max(fan->min, (s32)mpu1->rminn_intake_fan);
		fan->max = min(fan->max, (s32)mpu1->rmaxn_intake_fan);
		goto bail;
	}
	if (mpu0 && !strcmp(fan->ctrl.name, "cpu-rear-fan-0")) {
		fan->min = max(fan->min, (s32)mpu0->rminn_exhaust_fan);
		fan->max = min(fan->max, (s32)mpu0->rmaxn_exhaust_fan);
		goto bail;
	}
	if (mpu1 && !strcmp(fan->ctrl.name, "cpu-rear-fan-1")) {
		fan->min = max(fan->min, (s32)mpu1->rminn_exhaust_fan);
		fan->max = min(fan->max, (s32)mpu1->rmaxn_exhaust_fan);
		goto bail;
	}
	/* Rackmac variants, we just use mpu0 intake */
	if (!strncmp(fan->ctrl.name, "cpu-fan", 7)) {
		fan->min = max(fan->min, (s32)mpu0->rminn_intake_fan);
		fan->max = min(fan->max, (s32)mpu0->rmaxn_intake_fan);
		goto bail;
	}
 bail:
	DBG("wf_fcu: fan min/max for %s set to: [%d..%d] RPM\n",
	    fan->ctrl.name, fan->min, fan->max);
}