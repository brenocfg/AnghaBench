#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int polling_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int interval ; 
 int kernelmode ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/  thermal_zone_device_update (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* thz_dev ; 

__attribute__((used)) static inline void acerhdf_enable_kernelmode(void)
{
	kernelmode = 1;

	thz_dev->polling_delay = interval*1000;
	thermal_zone_device_update(thz_dev, THERMAL_EVENT_UNSPECIFIED);
	pr_notice("kernel mode fan control ON\n");
}