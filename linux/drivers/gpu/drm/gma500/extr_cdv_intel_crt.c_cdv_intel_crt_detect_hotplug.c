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
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int CRT_HOTPLUG_ACTIVATION_PERIOD_64 ; 
 int CRT_HOTPLUG_DETECT_MASK ; 
 int CRT_HOTPLUG_FORCE_DETECT ; 
 int CRT_HOTPLUG_INT_STATUS ; 
 int CRT_HOTPLUG_MONITOR_MASK ; 
 int CRT_HOTPLUG_MONITOR_NONE ; 
 int CRT_HOTPLUG_VOLTAGE_COMPARE_50 ; 
 int /*<<< orphan*/  PORT_HOTPLUG_EN ; 
 int /*<<< orphan*/  PORT_HOTPLUG_STAT ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static bool cdv_intel_crt_detect_hotplug(struct drm_connector *connector,
								bool force)
{
	struct drm_device *dev = connector->dev;
	u32 hotplug_en;
	int i, tries = 0, ret = false;
	u32 orig;

	/*
	 * On a CDV thep, CRT detect sequence need to be done twice
	 * to get a reliable result.
	 */
	tries = 2;

	orig = hotplug_en = REG_READ(PORT_HOTPLUG_EN);
	hotplug_en &= ~(CRT_HOTPLUG_DETECT_MASK);
	hotplug_en |= CRT_HOTPLUG_FORCE_DETECT;

	hotplug_en |= CRT_HOTPLUG_ACTIVATION_PERIOD_64;
	hotplug_en |= CRT_HOTPLUG_VOLTAGE_COMPARE_50;

	for (i = 0; i < tries ; i++) {
		unsigned long timeout;
		/* turn on the FORCE_DETECT */
		REG_WRITE(PORT_HOTPLUG_EN, hotplug_en);
		timeout = jiffies + msecs_to_jiffies(1000);
		/* wait for FORCE_DETECT to go off */
		do {
			if (!(REG_READ(PORT_HOTPLUG_EN) &
					CRT_HOTPLUG_FORCE_DETECT))
				break;
			msleep(1);
		} while (time_after(timeout, jiffies));
	}

	if ((REG_READ(PORT_HOTPLUG_STAT) & CRT_HOTPLUG_MONITOR_MASK) !=
	    CRT_HOTPLUG_MONITOR_NONE)
		ret = true;

	 /* clear the interrupt we just generated, if any */
	REG_WRITE(PORT_HOTPLUG_STAT, CRT_HOTPLUG_INT_STATUS);

	/* and put the bits back */
	REG_WRITE(PORT_HOTPLUG_EN, orig);
	return ret;
}