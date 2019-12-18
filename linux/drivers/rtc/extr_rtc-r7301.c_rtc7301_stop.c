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
 int /*<<< orphan*/  RTC7301_CONTROL ; 
 int /*<<< orphan*/  RTC7301_CONTROL_STOP ; 
 int /*<<< orphan*/  rtc7301_update_bits (struct rtc7301_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtc7301_stop(struct rtc7301_priv *priv)
{
	rtc7301_update_bits(priv, RTC7301_CONTROL, RTC7301_CONTROL_STOP,
			    RTC7301_CONTROL_STOP);
}