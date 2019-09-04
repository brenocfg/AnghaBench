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
typedef  int u32 ;

/* Variables and functions */
 int FREF ; 
 int MAX_LPD ; 
 int /*<<< orphan*/  MCF_CCM_CDR ; 
 int MCF_CCM_CDR_LPDIV (int) ; 
 int MCF_CCM_CDR_SSIDIV (int) ; 
 int /*<<< orphan*/  MCF_CCM_MISCCR ; 
 int MCF_CCM_MISCCR_LIMP ; 
 int MIN_LPD ; 
 int readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

int clock_limp(int div)
{
	u32 temp;

	/* Check bounds of divider */
	if (div < MIN_LPD)
		div = MIN_LPD;
	if (div > MAX_LPD)
		div = MAX_LPD;
    
	/* Save of the current value of the SSIDIV so we don't
	   overwrite the value*/
	temp = readw(MCF_CCM_CDR) & MCF_CCM_CDR_SSIDIV(0xF);
      
	/* Apply the divider to the system clock */
	writew(MCF_CCM_CDR_LPDIV(div) | MCF_CCM_CDR_SSIDIV(temp), MCF_CCM_CDR);
    
	writew(readw(MCF_CCM_MISCCR) | MCF_CCM_MISCCR_LIMP, MCF_CCM_MISCCR);
    
	return (FREF/(3*(1 << div)));
}