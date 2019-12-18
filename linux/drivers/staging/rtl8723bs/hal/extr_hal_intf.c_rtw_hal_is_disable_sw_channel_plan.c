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
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  bDisableSWChannelPlan; } ;

/* Variables and functions */
 TYPE_1__* GET_HAL_DATA (struct adapter*) ; 

s32 rtw_hal_is_disable_sw_channel_plan(struct adapter *padapter)
{
	return GET_HAL_DATA(padapter)->bDisableSWChannelPlan;
}