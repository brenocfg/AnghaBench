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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
#define  PWR_MODE_BTN_ONLY 130 
#define  PWR_MODE_FULL_ACTIVE 129 
#define  PWR_MODE_OFF 128 
 int /*<<< orphan*/  cyapa_pwr_cmd_to_sleep_time (int) ; 

__attribute__((used)) static u16 cyapa_get_wait_time_for_pwr_cmd(u8 pwr_mode)
{
	switch (pwr_mode) {
	case PWR_MODE_FULL_ACTIVE: return 20;
	case PWR_MODE_BTN_ONLY: return 20;
	case PWR_MODE_OFF: return 20;
	default: return cyapa_pwr_cmd_to_sleep_time(pwr_mode) + 50;
	}
}