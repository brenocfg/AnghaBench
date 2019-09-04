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
typedef  scalar_t__ u8 ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MMC_BUS_TEST_R ; 
 int /*<<< orphan*/  MMC_BUS_TEST_W ; 
 scalar_t__ MMC_BUS_WIDTH_1 ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_BUS_WIDTH_8 ; 
 int mmc_send_bus_test (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mmc_bus_test(struct mmc_card *card, u8 bus_width)
{
	int width;

	if (bus_width == MMC_BUS_WIDTH_8)
		width = 8;
	else if (bus_width == MMC_BUS_WIDTH_4)
		width = 4;
	else if (bus_width == MMC_BUS_WIDTH_1)
		return 0; /* no need for test */
	else
		return -EINVAL;

	/*
	 * Ignore errors from BUS_TEST_W.  BUS_TEST_R will fail if there
	 * is a problem.  This improves chances that the test will work.
	 */
	mmc_send_bus_test(card, card->host, MMC_BUS_TEST_W, width);
	return mmc_send_bus_test(card, card->host, MMC_BUS_TEST_R, width);
}