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
struct dst_state {int inversion; int* tx_tuna; } ;
typedef  enum fe_spectral_inversion { ____Placeholder_fe_spectral_inversion } fe_spectral_inversion ;

/* Variables and functions */
 int EINVAL ; 
#define  INVERSION_OFF 129 
#define  INVERSION_ON 128 

__attribute__((used)) static int dst_set_inversion(struct dst_state *state,
			     enum fe_spectral_inversion inversion)
{
	state->inversion = inversion;
	switch (inversion) {
	case INVERSION_OFF:	/*	Inversion = Normal	*/
		state->tx_tuna[8] &= ~0x80;
		break;
	case INVERSION_ON:
		state->tx_tuna[8] |= 0x80;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}