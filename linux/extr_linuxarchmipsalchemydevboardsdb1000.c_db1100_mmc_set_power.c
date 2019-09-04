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

/* Variables and functions */
 int /*<<< orphan*/  BCSR_BOARD ; 
 int BCSR_BOARD_PB1100_SD0PWR ; 
 int BCSR_BOARD_SD0PWR ; 
 int /*<<< orphan*/  BCSR_WHOAMI ; 
 scalar_t__ BCSR_WHOAMI_BOARD (int /*<<< orphan*/ ) ; 
 scalar_t__ BCSR_WHOAMI_DB1100 ; 
 int /*<<< orphan*/  bcsr_mod (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bcsr_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void db1100_mmc_set_power(void *mmc_host, int state)
{
	int bit;

	if (BCSR_WHOAMI_BOARD(bcsr_read(BCSR_WHOAMI)) == BCSR_WHOAMI_DB1100)
		bit = BCSR_BOARD_SD0PWR;
	else
		bit = BCSR_BOARD_PB1100_SD0PWR;

	if (state) {
		bcsr_mod(BCSR_BOARD, 0, bit);
		msleep(400);	/* stabilization time */
	} else
		bcsr_mod(BCSR_BOARD, bit, 0);
}