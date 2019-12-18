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

/* Variables and functions */
#define  MXT_GEN_ACQUIRE_T8 153 
#define  MXT_GEN_COMMAND_T6 152 
#define  MXT_GEN_DATASOURCE_T53 151 
#define  MXT_GEN_POWER_T7 150 
#define  MXT_PROCG_NOISESUPPRESSION_T48 149 
#define  MXT_PROCG_NOISE_T22 148 
#define  MXT_PROCI_GRIPFACE_T20 147 
#define  MXT_PROCI_GRIP_T40 146 
#define  MXT_PROCI_ONETOUCH_T24 145 
#define  MXT_PROCI_PALM_T41 144 
#define  MXT_PROCI_STYLUS_T47 143 
#define  MXT_PROCI_TOUCHSUPPRESSION_T42 142 
#define  MXT_PROCI_TWOTOUCH_T27 141 
#define  MXT_SPT_COMMSCONFIG_T18 140 
#define  MXT_SPT_CTECONFIG_T28 139 
#define  MXT_SPT_CTECONFIG_T46 138 
#define  MXT_SPT_DIGITIZER_T43 137 
#define  MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71 136 
#define  MXT_SPT_GPIOPWM_T19 135 
#define  MXT_SPT_SELFTEST_T25 134 
#define  MXT_SPT_USERDATA_T38 133 
#define  MXT_TOUCH_KEYARRAY_T15 132 
#define  MXT_TOUCH_MULTITOUCHSCREEN_T100 131 
#define  MXT_TOUCH_MULTI_T9 130 
#define  MXT_TOUCH_PROXIMITY_T23 129 
#define  MXT_TOUCH_PROXKEY_T52 128 

__attribute__((used)) static bool mxt_object_readable(unsigned int type)
{
	switch (type) {
	case MXT_GEN_COMMAND_T6:
	case MXT_GEN_POWER_T7:
	case MXT_GEN_ACQUIRE_T8:
	case MXT_GEN_DATASOURCE_T53:
	case MXT_TOUCH_MULTI_T9:
	case MXT_TOUCH_KEYARRAY_T15:
	case MXT_TOUCH_PROXIMITY_T23:
	case MXT_TOUCH_PROXKEY_T52:
	case MXT_TOUCH_MULTITOUCHSCREEN_T100:
	case MXT_PROCI_GRIPFACE_T20:
	case MXT_PROCG_NOISE_T22:
	case MXT_PROCI_ONETOUCH_T24:
	case MXT_PROCI_TWOTOUCH_T27:
	case MXT_PROCI_GRIP_T40:
	case MXT_PROCI_PALM_T41:
	case MXT_PROCI_TOUCHSUPPRESSION_T42:
	case MXT_PROCI_STYLUS_T47:
	case MXT_PROCG_NOISESUPPRESSION_T48:
	case MXT_SPT_COMMSCONFIG_T18:
	case MXT_SPT_GPIOPWM_T19:
	case MXT_SPT_SELFTEST_T25:
	case MXT_SPT_CTECONFIG_T28:
	case MXT_SPT_USERDATA_T38:
	case MXT_SPT_DIGITIZER_T43:
	case MXT_SPT_CTECONFIG_T46:
	case MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71:
		return true;
	default:
		return false;
	}
}