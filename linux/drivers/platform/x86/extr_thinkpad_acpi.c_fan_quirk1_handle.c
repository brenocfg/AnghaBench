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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ fan_ctrl_status_undef; } ;

/* Variables and functions */
 scalar_t__ TP_EC_FAN_AUTO ; 
 scalar_t__ fan_control_initial_status ; 
 TYPE_1__ tp_features ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static void fan_quirk1_handle(u8 *fan_status)
{
	if (unlikely(tp_features.fan_ctrl_status_undef)) {
		if (*fan_status != fan_control_initial_status) {
			/* something changed the HFSP regisnter since
			 * driver init time, so it is not undefined
			 * anymore */
			tp_features.fan_ctrl_status_undef = 0;
		} else {
			/* Return most likely status. In fact, it
			 * might be the only possible status */
			*fan_status = TP_EC_FAN_AUTO;
		}
	}
}