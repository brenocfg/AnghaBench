#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_5__ {int serial_signals; int port_num; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 int BIT0 ; 
 int BIT1 ; 
 int BIT2 ; 
 int BIT3 ; 
 int /*<<< orphan*/  SR3 ; 
 int SerialSignal_CTS ; 
 int SerialSignal_DCD ; 
 int SerialSignal_DSR ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RI ; 
 int SerialSignal_RTS ; 
 int read_reg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int read_status_reg (TYPE_1__*) ; 

__attribute__((used)) static void get_signals(SLMP_INFO *info)
{
	u16 status = read_reg(info, SR3);
	u16 gpstatus = read_status_reg(info);
	u16 testbit;

	/* clear all serial signals except RTS and DTR */
	info->serial_signals &= SerialSignal_RTS | SerialSignal_DTR;

	/* set serial signal bits to reflect MISR */

	if (!(status & BIT3))
		info->serial_signals |= SerialSignal_CTS;

	if ( !(status & BIT2))
		info->serial_signals |= SerialSignal_DCD;

	testbit = BIT1 << (info->port_num * 2); // Port 0..3 RI is GPDATA<1,3,5,7>
	if (!(gpstatus & testbit))
		info->serial_signals |= SerialSignal_RI;

	testbit = BIT0 << (info->port_num * 2); // Port 0..3 DSR is GPDATA<0,2,4,6>
	if (!(gpstatus & testbit))
		info->serial_signals |= SerialSignal_DSR;
}