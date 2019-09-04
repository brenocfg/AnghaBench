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

/* Variables and functions */
 int CRT_HOTPLUG_INT_EN ; 
 int HDMIB_HOTPLUG_INT_EN ; 
 int HDMIC_HOTPLUG_INT_EN ; 
 int HDMID_HOTPLUG_INT_EN ; 
 int /*<<< orphan*/  PORT_HOTPLUG_EN ; 
 int /*<<< orphan*/  PORT_HOTPLUG_STAT ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cdv_hotplug_enable(struct drm_device *dev, bool on)
{
	if (on) {
		u32 hotplug = REG_READ(PORT_HOTPLUG_EN);
		hotplug |= HDMIB_HOTPLUG_INT_EN | HDMIC_HOTPLUG_INT_EN |
			   HDMID_HOTPLUG_INT_EN | CRT_HOTPLUG_INT_EN;
		REG_WRITE(PORT_HOTPLUG_EN, hotplug);
	}  else {
		REG_WRITE(PORT_HOTPLUG_EN, 0);
		REG_WRITE(PORT_HOTPLUG_STAT, REG_READ(PORT_HOTPLUG_STAT));
	}	
}