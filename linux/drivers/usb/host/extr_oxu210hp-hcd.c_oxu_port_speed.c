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
struct oxu_hcd {int dummy; } ;

/* Variables and functions */
 unsigned int USB_PORT_STAT_HIGH_SPEED ; 
 unsigned int USB_PORT_STAT_LOW_SPEED ; 

__attribute__((used)) static inline unsigned int oxu_port_speed(struct oxu_hcd *oxu,
						unsigned int portsc)
{
	switch ((portsc >> 26) & 3) {
	case 0:
		return 0;
	case 1:
		return USB_PORT_STAT_LOW_SPEED;
	case 2:
	default:
		return USB_PORT_STAT_HIGH_SPEED;
	}
}