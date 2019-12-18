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
struct vme_bridge {struct fake_driver* driver_priv; } ;
struct fake_driver {int /*<<< orphan*/  int_statid; int /*<<< orphan*/  int_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  vme_irq_handler (struct vme_bridge*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fake_VIRQ_tasklet(unsigned long data)
{
	struct vme_bridge *fake_bridge;
	struct fake_driver *bridge;

	fake_bridge = (struct vme_bridge *) data;
	bridge = fake_bridge->driver_priv;

	vme_irq_handler(fake_bridge, bridge->int_level, bridge->int_statid);
}