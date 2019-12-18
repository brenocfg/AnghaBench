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
struct rtc7301_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC7301_ALARM_CONTROL ; 
 int RTC7301_ALARM_CONTROL_AF ; 
 int RTC7301_ALARM_CONTROL_AIE ; 
 int /*<<< orphan*/  rtc7301_update_bits (struct rtc7301_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtc7301_alarm_irq(struct rtc7301_priv *priv, unsigned int enabled)
{
	rtc7301_update_bits(priv, RTC7301_ALARM_CONTROL,
			    RTC7301_ALARM_CONTROL_AF |
			    RTC7301_ALARM_CONTROL_AIE,
			    enabled ? RTC7301_ALARM_CONTROL_AIE : 0);
}