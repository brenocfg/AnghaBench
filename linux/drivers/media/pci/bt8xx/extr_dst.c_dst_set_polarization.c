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
struct dst_state {int voltage; int* tx_tuna; } ;

/* Variables and functions */
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int dst_set_polarization(struct dst_state *state)
{
	switch (state->voltage) {
	case SEC_VOLTAGE_13:	/*	Vertical	*/
		dprintk(2, "Polarization=[Vertical]\n");
		state->tx_tuna[8] &= ~0x40;
		break;
	case SEC_VOLTAGE_18:	/*	Horizontal	*/
		dprintk(2, "Polarization=[Horizontal]\n");
		state->tx_tuna[8] |= 0x40;
		break;
	case SEC_VOLTAGE_OFF:
		break;
	}

	return 0;
}