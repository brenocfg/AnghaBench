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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qca8k_priv {int dummy; } ;
struct dsa_switch {scalar_t__ priv; } ;

/* Variables and functions */
#define  BR_STATE_BLOCKING 132 
#define  BR_STATE_DISABLED 131 
#define  BR_STATE_FORWARDING 130 
#define  BR_STATE_LEARNING 129 
#define  BR_STATE_LISTENING 128 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_CTRL (int) ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_STATE_BLOCKING ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_STATE_DISABLED ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_STATE_FORWARD ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_STATE_LEARNING ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_STATE_LISTENING ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_STATE_MASK ; 
 int /*<<< orphan*/  qca8k_rmw (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qca8k_port_stp_state_set(struct dsa_switch *ds, int port, u8 state)
{
	struct qca8k_priv *priv = (struct qca8k_priv *)ds->priv;
	u32 stp_state;

	switch (state) {
	case BR_STATE_DISABLED:
		stp_state = QCA8K_PORT_LOOKUP_STATE_DISABLED;
		break;
	case BR_STATE_BLOCKING:
		stp_state = QCA8K_PORT_LOOKUP_STATE_BLOCKING;
		break;
	case BR_STATE_LISTENING:
		stp_state = QCA8K_PORT_LOOKUP_STATE_LISTENING;
		break;
	case BR_STATE_LEARNING:
		stp_state = QCA8K_PORT_LOOKUP_STATE_LEARNING;
		break;
	case BR_STATE_FORWARDING:
	default:
		stp_state = QCA8K_PORT_LOOKUP_STATE_FORWARD;
		break;
	}

	qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(port),
		  QCA8K_PORT_LOOKUP_STATE_MASK, stp_state);
}