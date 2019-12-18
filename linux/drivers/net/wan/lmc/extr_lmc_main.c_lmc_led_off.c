#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int lmc_miireg16; int /*<<< orphan*/  lmc_device; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  lmc_mii_writereg (TYPE_1__* const,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lmc_trace (int /*<<< orphan*/ ,char*) ; 

void lmc_led_off(lmc_softc_t * const sc, u32 led) /*fold00*/
{
    lmc_trace(sc->lmc_device, "lmc_led_off in");
    if(sc->lmc_miireg16 & led){ /* Already set don't do anything */
        lmc_trace(sc->lmc_device, "lmc_led_off aoff out");
        return;
    }
    
    sc->lmc_miireg16 |= led;
    lmc_mii_writereg(sc, 0, 16, sc->lmc_miireg16);
    lmc_trace(sc->lmc_device, "lmc_led_off out");
}