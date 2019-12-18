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
struct s5m_rtc_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct s5m_rtc_info* dev_get_drvdata (struct device*) ; 
 int s5m_rtc_start_alarm (struct s5m_rtc_info*) ; 
 int s5m_rtc_stop_alarm (struct s5m_rtc_info*) ; 

__attribute__((used)) static int s5m_rtc_alarm_irq_enable(struct device *dev,
				    unsigned int enabled)
{
	struct s5m_rtc_info *info = dev_get_drvdata(dev);

	if (enabled)
		return s5m_rtc_start_alarm(info);
	else
		return s5m_rtc_stop_alarm(info);
}