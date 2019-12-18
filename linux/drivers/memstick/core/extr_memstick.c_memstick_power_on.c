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
struct memstick_host {int (* set_param ) (struct memstick_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MEMSTICK_INTERFACE ; 
 int /*<<< orphan*/  MEMSTICK_POWER ; 
 int /*<<< orphan*/  MEMSTICK_POWER_ON ; 
 int /*<<< orphan*/  MEMSTICK_SERIAL ; 
 int stub1 (struct memstick_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct memstick_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int memstick_power_on(struct memstick_host *host)
{
	int rc = host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_ON);

	if (!rc)
		rc = host->set_param(host, MEMSTICK_INTERFACE, MEMSTICK_SERIAL);

	return rc;
}