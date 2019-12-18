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
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int mmc_gpio_get_cd (struct mmc_host*) ; 

__attribute__((used)) static int meson_mmc_get_cd(struct mmc_host *mmc)
{
	int status = mmc_gpio_get_cd(mmc);

	if (status == -ENOSYS)
		return 1; /* assume present */

	return status;
}