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
struct TYPE_2__ {int /*<<< orphan*/  msg; scalar_t__ len; } ;
struct cec_pin {int tx_generated_poll; int tx_post_eom; scalar_t__ state; int tx_toggle; int rx_toggle; int /*<<< orphan*/  ts; TYPE_1__ rx_msg; scalar_t__ tx_bit; scalar_t__ rx_bit; } ;

/* Variables and functions */
 scalar_t__ CEC_ST_IDLE ; 
 scalar_t__ CEC_ST_RX_LOW_DRIVE ; 
 scalar_t__ CEC_ST_RX_START_BIT_LOW ; 
 scalar_t__ CEC_ST_TX_LOW_DRIVE ; 
 scalar_t__ CEC_ST_TX_WAIT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cec_pin_to_idle(struct cec_pin *pin)
{
	/*
	 * Reset all status fields, release the bus and
	 * go to idle state.
	 */
	pin->rx_bit = pin->tx_bit = 0;
	pin->rx_msg.len = 0;
	memset(pin->rx_msg.msg, 0, sizeof(pin->rx_msg.msg));
	pin->ts = ns_to_ktime(0);
	pin->tx_generated_poll = false;
	pin->tx_post_eom = false;
	if (pin->state >= CEC_ST_TX_WAIT &&
	    pin->state <= CEC_ST_TX_LOW_DRIVE)
		pin->tx_toggle ^= 1;
	if (pin->state >= CEC_ST_RX_START_BIT_LOW &&
	    pin->state <= CEC_ST_RX_LOW_DRIVE)
		pin->rx_toggle ^= 1;
	pin->state = CEC_ST_IDLE;
}