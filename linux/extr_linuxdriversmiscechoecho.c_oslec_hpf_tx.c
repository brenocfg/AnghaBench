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
struct oslec_state {int adaption_mode; int tx_1; int tx_2; } ;
typedef  int int16_t ;

/* Variables and functions */
 int DC_LOG2BETA ; 
 int ECHO_CAN_USE_TX_HPF ; 

int16_t oslec_hpf_tx(struct oslec_state *ec, int16_t tx)
{
	int tmp;
	int tmp1;

	if (ec->adaption_mode & ECHO_CAN_USE_TX_HPF) {
		tmp = tx << 15;

		/*
		 * Make sure the gain of the HPF is 1.0. The first can still
		 * saturate a little under impulse conditions, and it might
		 * roll to 32768 and need clipping on sustained peak level
		 * signals. However, the scale of such clipping is small, and
		 * the error due to any saturation should not markedly affect
		 * the downstream processing.
		 */
		tmp -= (tmp >> 4);

		ec->tx_1 += -(ec->tx_1 >> DC_LOG2BETA) + tmp - ec->tx_2;
		tmp1 = ec->tx_1 >> 15;
		if (tmp1 > 32767)
			tmp1 = 32767;
		if (tmp1 < -32767)
			tmp1 = -32767;
		tx = tmp1;
		ec->tx_2 = tmp;
	}

	return tx;
}