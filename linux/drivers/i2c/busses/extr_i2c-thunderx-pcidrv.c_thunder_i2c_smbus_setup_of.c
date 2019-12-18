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
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct octeon_i2c {int /*<<< orphan*/  ara; TYPE_1__ alert_data; int /*<<< orphan*/  adap; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  i2c_setup_smbus_alert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thunder_i2c_smbus_setup_of(struct octeon_i2c *i2c,
				      struct device_node *node)
{
	if (!node)
		return -EINVAL;

	i2c->alert_data.irq = irq_of_parse_and_map(node, 0);
	if (!i2c->alert_data.irq)
		return -EINVAL;

	i2c->ara = i2c_setup_smbus_alert(&i2c->adap, &i2c->alert_data);
	if (!i2c->ara)
		return -ENODEV;
	return 0;
}