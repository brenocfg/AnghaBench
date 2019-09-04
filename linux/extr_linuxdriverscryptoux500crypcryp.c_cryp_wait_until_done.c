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
struct cryp_device_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ cryp_is_logic_busy (struct cryp_device_data*) ; 

void cryp_wait_until_done(struct cryp_device_data *device_data)
{
	while (cryp_is_logic_busy(device_data))
		cpu_relax();
}