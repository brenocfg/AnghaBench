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
struct usb_hub {TYPE_1__* descriptor; } ;
struct TYPE_2__ {int bPwrOn2PwrGood; } ;

/* Variables and functions */
 int max (unsigned int,unsigned int) ; 

__attribute__((used)) static inline unsigned hub_power_on_good_delay(struct usb_hub *hub)
{
	unsigned delay = hub->descriptor->bPwrOn2PwrGood * 2;

	/* Wait at least 100 msec for power to become stable */
	return max(delay, 100U);
}