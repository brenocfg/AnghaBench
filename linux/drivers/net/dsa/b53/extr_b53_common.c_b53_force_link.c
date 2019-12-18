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
struct b53_device {int cpu_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_GMII_PORT_OVERRIDE_CTRL (int) ; 
 int /*<<< orphan*/  B53_PORT_OVERRIDE_CTRL ; 
 int /*<<< orphan*/  GMII_PO_EN ; 
 int /*<<< orphan*/  PORT_OVERRIDE_EN ; 
 int /*<<< orphan*/  PORT_OVERRIDE_LINK ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b53_force_link(struct b53_device *dev, int port, int link)
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
	if (link)
		reg |= PORT_OVERRIDE_LINK;
	else
		reg &= ~PORT_OVERRIDE_LINK;
	b53_write8(dev, B53_CTRL_PAGE, off, reg);
}