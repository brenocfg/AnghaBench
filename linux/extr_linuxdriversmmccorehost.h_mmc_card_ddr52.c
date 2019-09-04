#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmc_card {TYPE_2__* host; } ;
struct TYPE_3__ {scalar_t__ timing; } ;
struct TYPE_4__ {TYPE_1__ ios; } ;

/* Variables and functions */
 scalar_t__ MMC_TIMING_MMC_DDR52 ; 

__attribute__((used)) static inline bool mmc_card_ddr52(struct mmc_card *card)
{
	return card->host->ios.timing == MMC_TIMING_MMC_DDR52;
}