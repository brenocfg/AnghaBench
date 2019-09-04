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
struct cvm_mmc_host {int /*<<< orphan*/  global_pwr_gpiod; int /*<<< orphan*/  shared_power_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void octeon_mmc_set_shared_power(struct cvm_mmc_host *host, int dir)
{
	if (dir == 0)
		if (!atomic_dec_return(&host->shared_power_users))
			gpiod_set_value_cansleep(host->global_pwr_gpiod, 0);
	if (dir == 1)
		if (atomic_inc_return(&host->shared_power_users) == 1)
			gpiod_set_value_cansleep(host->global_pwr_gpiod, 1);
}