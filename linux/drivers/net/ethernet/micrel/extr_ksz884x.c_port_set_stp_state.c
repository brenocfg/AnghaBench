#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ksz_hw {TYPE_2__* ksz_switch; } ;
struct TYPE_4__ {TYPE_1__* port_cfg; } ;
struct TYPE_3__ {int stp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS8842_PORT_CTRL_2_OFFSET ; 
 int PORT_LEARN_DISABLE ; 
 int PORT_RX_ENABLE ; 
 int PORT_TX_ENABLE ; 
#define  STP_STATE_BLOCKED 133 
#define  STP_STATE_DISABLED 132 
#define  STP_STATE_FORWARDING 131 
#define  STP_STATE_LEARNING 130 
#define  STP_STATE_LISTENING 129 
#define  STP_STATE_SIMPLE 128 
 int /*<<< orphan*/  port_r16 (struct ksz_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  port_w16 (struct ksz_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void port_set_stp_state(struct ksz_hw *hw, int port, int state)
{
	u16 data;

	port_r16(hw, port, KS8842_PORT_CTRL_2_OFFSET, &data);
	switch (state) {
	case STP_STATE_DISABLED:
		data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		break;
	case STP_STATE_LISTENING:
/*
 * No need to turn on transmit because of port direct mode.
 * Turning on receive is required if static MAC table is not setup.
 */
		data &= ~PORT_TX_ENABLE;
		data |= PORT_RX_ENABLE;
		data |= PORT_LEARN_DISABLE;
		break;
	case STP_STATE_LEARNING:
		data &= ~PORT_TX_ENABLE;
		data |= PORT_RX_ENABLE;
		data &= ~PORT_LEARN_DISABLE;
		break;
	case STP_STATE_FORWARDING:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data &= ~PORT_LEARN_DISABLE;
		break;
	case STP_STATE_BLOCKED:
/*
 * Need to setup static MAC table with override to keep receiving BPDU
 * messages.  See sw_init_stp routine.
 */
		data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		break;
	case STP_STATE_SIMPLE:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		break;
	}
	port_w16(hw, port, KS8842_PORT_CTRL_2_OFFSET, data);
	hw->ksz_switch->port_cfg[port].stp_state = state;
}