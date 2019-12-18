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
typedef  int u32 ;
typedef  scalar_t__ time64_t ;
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;
struct brcmstb_waketmr {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ BRCMSTB_WKTMR_ALARM ; 
 scalar_t__ BRCMSTB_WKTMR_EVENT ; 
 struct brcmstb_waketmr* dev_get_drvdata (struct device*) ; 
 void* readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmstb_waketmr_getalarm(struct device *dev,
				    struct rtc_wkalrm *alarm)
{
	struct brcmstb_waketmr *timer = dev_get_drvdata(dev);
	time64_t sec;
	u32 reg;

	sec = readl_relaxed(timer->base + BRCMSTB_WKTMR_ALARM);
	if (sec != 0) {
		/* Alarm is enabled */
		alarm->enabled = 1;
		rtc_time64_to_tm(sec, &alarm->time);
	}

	reg = readl_relaxed(timer->base + BRCMSTB_WKTMR_EVENT);
	alarm->pending = !!(reg & 1);

	return 0;
}