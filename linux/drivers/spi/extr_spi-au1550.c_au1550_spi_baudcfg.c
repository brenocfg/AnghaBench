#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct au1550_spi {TYPE_1__* pdata; } ;
struct TYPE_2__ {int mainclk_hz; } ;

/* Variables and functions */
 int PSC_SPICFG_SET_BAUD (int) ; 
 int PSC_SPICFG_SET_DIV (int) ; 

__attribute__((used)) static u32 au1550_spi_baudcfg(struct au1550_spi *hw, unsigned speed_hz)
{
	u32 mainclk_hz = hw->pdata->mainclk_hz;
	u32 div, brg;

	for (div = 0; div < 4; div++) {
		brg = mainclk_hz / speed_hz / (4 << div);
		/* now we have BRG+1 in brg, so count with that */
		if (brg < (4 + 1)) {
			brg = (4 + 1);	/* speed_hz too big */
			break;		/* set lowest brg (div is == 0) */
		}
		if (brg <= (63 + 1))
			break;		/* we have valid brg and div */
	}
	if (div == 4) {
		div = 3;		/* speed_hz too small */
		brg = (63 + 1);		/* set highest brg and div */
	}
	brg--;
	return PSC_SPICFG_SET_BAUD(brg) | PSC_SPICFG_SET_DIV(div);
}