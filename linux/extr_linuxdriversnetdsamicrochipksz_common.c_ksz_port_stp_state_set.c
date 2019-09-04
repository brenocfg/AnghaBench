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
struct ksz_device {int dummy; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct ksz_device* priv; } ;

/* Variables and functions */
#define  BR_STATE_BLOCKING 132 
#define  BR_STATE_DISABLED 131 
#define  BR_STATE_FORWARDING 130 
#define  BR_STATE_LEARNING 129 
#define  BR_STATE_LISTENING 128 
 int PORT_LEARN_DISABLE ; 
 int PORT_RX_ENABLE ; 
 int PORT_TX_ENABLE ; 
 int /*<<< orphan*/  P_STP_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_pwrite8 (struct ksz_device*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ksz_port_stp_state_set(struct dsa_switch *ds, int port, u8 state)
{
	struct ksz_device *dev = ds->priv;
	u8 data;

	ksz_pread8(dev, port, P_STP_CTRL, &data);
	data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE | PORT_LEARN_DISABLE);

	switch (state) {
	case BR_STATE_DISABLED:
		data |= PORT_LEARN_DISABLE;
		break;
	case BR_STATE_LISTENING:
		data |= (PORT_RX_ENABLE | PORT_LEARN_DISABLE);
		break;
	case BR_STATE_LEARNING:
		data |= PORT_RX_ENABLE;
		break;
	case BR_STATE_FORWARDING:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		break;
	case BR_STATE_BLOCKING:
		data |= PORT_LEARN_DISABLE;
		break;
	default:
		dev_err(ds->dev, "invalid STP state: %d\n", state);
		return;
	}

	ksz_pwrite8(dev, port, P_STP_CTRL, data);
}