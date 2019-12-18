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
struct TYPE_2__ {scalar_t__ phys_granted_power; scalar_t__ phys_waiting; int /*<<< orphan*/  requesters; int /*<<< orphan*/  timer; } ;
struct isci_host {TYPE_1__ power_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  power_control_timeout ; 
 int /*<<< orphan*/  sci_init_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sci_controller_initialize_power_control(struct isci_host *ihost)
{
	sci_init_timer(&ihost->power_control.timer, power_control_timeout);

	memset(ihost->power_control.requesters, 0,
	       sizeof(ihost->power_control.requesters));

	ihost->power_control.phys_waiting = 0;
	ihost->power_control.phys_granted_power = 0;
}