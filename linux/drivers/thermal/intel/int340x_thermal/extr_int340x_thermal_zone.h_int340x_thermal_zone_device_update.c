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
struct int34x_thermal_zone {int /*<<< orphan*/  zone; } ;
typedef  enum thermal_notify_event { ____Placeholder_thermal_notify_event } thermal_notify_event ;

/* Variables and functions */
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void int340x_thermal_zone_device_update(
					struct int34x_thermal_zone *tzone,
					enum thermal_notify_event event)
{
	thermal_zone_device_update(tzone->zone, event);
}