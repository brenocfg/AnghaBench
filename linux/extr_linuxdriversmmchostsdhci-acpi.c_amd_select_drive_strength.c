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
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int MMC_SET_DRIVER_TYPE_A ; 

__attribute__((used)) static int amd_select_drive_strength(struct mmc_card *card,
				     unsigned int max_dtr, int host_drv,
				     int card_drv, int *drv_type)
{
	return MMC_SET_DRIVER_TYPE_A;
}