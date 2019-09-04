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
 unsigned int MMC_DATA_READ ; 

__attribute__((used)) static int omap_hsmmc_multi_io_quirk(struct mmc_card *card,
				     unsigned int direction, int blk_size)
{
	/* This controller can't do multiblock reads due to hw bugs */
	if (direction == MMC_DATA_READ)
		return 1;

	return blk_size;
}