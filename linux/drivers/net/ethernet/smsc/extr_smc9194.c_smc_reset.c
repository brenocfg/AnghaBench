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
 scalar_t__ CONTROL ; 
 int CTL_AUTO_RELEASE ; 
 scalar_t__ INT_MASK ; 
 int MC_RESET ; 
 scalar_t__ MMU_CMD ; 
 scalar_t__ RCR ; 
 int RCR_CLEAR ; 
 int RCR_SOFTRESET ; 
 int /*<<< orphan*/  SMC_DELAY () ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 scalar_t__ TCR ; 
 int TCR_CLEAR ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void smc_reset( int ioaddr )
{
	/* This resets the registers mostly to defaults, but doesn't
	   affect EEPROM.  That seems unnecessary */
	SMC_SELECT_BANK( 0 );
	outw( RCR_SOFTRESET, ioaddr + RCR );

	/* this should pause enough for the chip to be happy */
	SMC_DELAY( );

	/* Set the transmit and receive configuration registers to
	   default values */
	outw( RCR_CLEAR, ioaddr + RCR );
	outw( TCR_CLEAR, ioaddr + TCR );

	/* set the control register to automatically
	   release successfully transmitted packets, to make the best
	   use out of our limited memory */
	SMC_SELECT_BANK( 1 );
	outw( inw( ioaddr + CONTROL ) | CTL_AUTO_RELEASE , ioaddr + CONTROL );

	/* Reset the MMU */
	SMC_SELECT_BANK( 2 );
	outw( MC_RESET, ioaddr + MMU_CMD );

	/* Note:  It doesn't seem that waiting for the MMU busy is needed here,
	   but this is a place where future chipsets _COULD_ break.  Be wary
 	   of issuing another MMU command right after this */

	outb( 0, ioaddr + INT_MASK );
}