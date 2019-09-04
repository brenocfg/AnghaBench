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
struct TYPE_2__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_idle_driver ; 
 void* at91_standby ; 
 int cpuidle_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at91_cpuidle_probe(struct platform_device *dev)
{
	at91_standby = (void *)(dev->dev.platform_data);
	
	return cpuidle_register(&at91_idle_driver, NULL);
}