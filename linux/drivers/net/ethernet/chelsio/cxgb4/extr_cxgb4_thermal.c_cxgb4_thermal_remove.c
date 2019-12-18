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
struct TYPE_2__ {scalar_t__ tzdev; } ;
struct adapter {TYPE_1__ ch_thermal; } ;

/* Variables and functions */
 int /*<<< orphan*/  thermal_zone_device_unregister (scalar_t__) ; 

int cxgb4_thermal_remove(struct adapter *adap)
{
	if (adap->ch_thermal.tzdev)
		thermal_zone_device_unregister(adap->ch_thermal.tzdev);
	return 0;
}