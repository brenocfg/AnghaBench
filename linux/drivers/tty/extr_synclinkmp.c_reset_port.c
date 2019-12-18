#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int serial_signals; scalar_t__ ie2_value; scalar_t__ ie1_value; scalar_t__ ie0_value; scalar_t__ sca_base; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ CHRESET ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  IE0 ; 
 int /*<<< orphan*/  IE1 ; 
 int /*<<< orphan*/  IE2 ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  rx_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  set_signals (TYPE_1__*) ; 
 int /*<<< orphan*/  tx_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void reset_port(SLMP_INFO *info)
{
	if (info->sca_base) {

		tx_stop(info);
		rx_stop(info);

		info->serial_signals &= ~(SerialSignal_RTS | SerialSignal_DTR);
		set_signals(info);

		/* disable all port interrupts */
		info->ie0_value = 0;
		info->ie1_value = 0;
		info->ie2_value = 0;
		write_reg(info, IE0, info->ie0_value);
		write_reg(info, IE1, info->ie1_value);
		write_reg(info, IE2, info->ie2_value);

		write_reg(info, CMD, CHRESET);
	}
}