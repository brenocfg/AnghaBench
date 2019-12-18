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
struct wf_ad7417_priv {TYPE_1__* mpu; } ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  bdiode; int /*<<< orphan*/  mdiode; } ;

/* Variables and functions */
 int ADC_12V_CURRENT_SCALE ; 
 int ADC_CPU_CURRENT_SCALE ; 
 int ADC_CPU_VOLTAGE_SCALE ; 

__attribute__((used)) static void wf_ad7417_adc_convert(struct wf_ad7417_priv *pv,
				  int chan, s32 raw, s32 *value)
{
	switch(chan) {
	case 1: /* Diode */
		*value = (raw * (s32)pv->mpu->mdiode +
			((s32)pv->mpu->bdiode << 12)) >> 2;
		break;
	case 2: /* 12v current */
		*value = raw * ADC_12V_CURRENT_SCALE;
		break;
	case 3: /* core voltage */
		*value = raw * ADC_CPU_VOLTAGE_SCALE;
		break;
	case 4: /* core current */
		*value = raw * ADC_CPU_CURRENT_SCALE;
		break;
	}
}