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
typedef  int /*<<< orphan*/  u8 ;
struct b53_device {int cpu_port; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_GMII_PORT_OVERRIDE_CTRL (int) ; 
 int /*<<< orphan*/  B53_PORT_OVERRIDE_CTRL ; 
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  GMII_PO_EN ; 
 int MLO_PAUSE_RX ; 
 int MLO_PAUSE_TX ; 
 int /*<<< orphan*/  PORT_OVERRIDE_EN ; 
 int /*<<< orphan*/  PORT_OVERRIDE_FULL_DUPLEX ; 
 int /*<<< orphan*/  PORT_OVERRIDE_RX_FLOW ; 
 int /*<<< orphan*/  PORT_OVERRIDE_SPEED_1000M ; 
 int /*<<< orphan*/  PORT_OVERRIDE_SPEED_100M ; 
 int /*<<< orphan*/  PORT_OVERRIDE_SPEED_10M ; 
 int /*<<< orphan*/  PORT_OVERRIDE_SPEED_2000M ; 
 int /*<<< orphan*/  PORT_OVERRIDE_TX_FLOW ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void b53_force_port_config(struct b53_device *dev, int port,
				  int speed, int duplex, int pause)
{
	u8 reg, val, off;

	/* Override the port settings */
	if (port == dev->cpu_port) {
		off = B53_PORT_OVERRIDE_CTRL;
		val = PORT_OVERRIDE_EN;
	} else {
		off = B53_GMII_PORT_OVERRIDE_CTRL(port);
		val = GMII_PO_EN;
	}

	b53_read8(dev, B53_CTRL_PAGE, off, &reg);
	reg |= val;
	if (duplex == DUPLEX_FULL)
		reg |= PORT_OVERRIDE_FULL_DUPLEX;
	else
		reg &= ~PORT_OVERRIDE_FULL_DUPLEX;

	switch (speed) {
	case 2000:
		reg |= PORT_OVERRIDE_SPEED_2000M;
		/* fallthrough */
	case SPEED_1000:
		reg |= PORT_OVERRIDE_SPEED_1000M;
		break;
	case SPEED_100:
		reg |= PORT_OVERRIDE_SPEED_100M;
		break;
	case SPEED_10:
		reg |= PORT_OVERRIDE_SPEED_10M;
		break;
	default:
		dev_err(dev->dev, "unknown speed: %d\n", speed);
		return;
	}

	if (pause & MLO_PAUSE_RX)
		reg |= PORT_OVERRIDE_RX_FLOW;
	if (pause & MLO_PAUSE_TX)
		reg |= PORT_OVERRIDE_TX_FLOW;

	b53_write8(dev, B53_CTRL_PAGE, off, reg);
}