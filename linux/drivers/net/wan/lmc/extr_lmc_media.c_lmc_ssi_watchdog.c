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
typedef  int u16 ;
typedef  int /*<<< orphan*/  lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_MII16_LED2 ; 
 int /*<<< orphan*/  lmc_led_off (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmc_led_on (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int lmc_mii_readreg (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lmc_ssi_watchdog(lmc_softc_t * const sc)
{
	u16 mii17 = lmc_mii_readreg(sc, 0, 17);
	if (((mii17 >> 3) & 7) == 7)
		lmc_led_off(sc, LMC_MII16_LED2);
	else
		lmc_led_on(sc, LMC_MII16_LED2);
}