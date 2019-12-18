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
struct b53_srab_port_priv {scalar_t__ mode; int /*<<< orphan*/  num; struct b53_device* dev; } ;
struct b53_device {int /*<<< orphan*/  ds; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  b53_port_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t b53_srab_port_thread(int irq, void *dev_id)
{
	struct b53_srab_port_priv *port = dev_id;
	struct b53_device *dev = port->dev;

	if (port->mode == PHY_INTERFACE_MODE_SGMII)
		b53_port_event(dev->ds, port->num);

	return IRQ_HANDLED;
}