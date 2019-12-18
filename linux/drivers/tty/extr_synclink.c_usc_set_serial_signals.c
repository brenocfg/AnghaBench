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
typedef  int /*<<< orphan*/  u16 ;
struct mgsl_struct {unsigned char serial_signals; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT4 ; 
 int /*<<< orphan*/  BIT6 ; 
 int /*<<< orphan*/  PCR ; 
 unsigned char SerialSignal_DTR ; 
 unsigned char SerialSignal_RTS ; 
 int /*<<< orphan*/  usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usc_set_serial_signals( struct mgsl_struct *info )
{
	u16 Control;
	unsigned char V24Out = info->serial_signals;

	/* get the current value of the Port Control Register (PCR) */

	Control = usc_InReg( info, PCR );

	if ( V24Out & SerialSignal_RTS )
		Control &= ~(BIT6);
	else
		Control |= BIT6;

	if ( V24Out & SerialSignal_DTR )
		Control &= ~(BIT4);
	else
		Control |= BIT4;

	usc_OutReg( info, PCR, Control );

}