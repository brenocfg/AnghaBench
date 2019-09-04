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
struct mal_instance {int num_rx_chans; int num_tx_chans; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NUM_RX_BUFF ; 
 int NUM_TX_BUFF ; 

int mal_rx_bd_offset(struct mal_instance *mal, int channel)
{
	BUG_ON(channel < 0 || channel >= mal->num_rx_chans);
	return mal->num_tx_chans * NUM_TX_BUFF + channel * NUM_RX_BUFF;
}