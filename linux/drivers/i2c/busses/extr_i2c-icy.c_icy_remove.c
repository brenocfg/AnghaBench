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
struct zorro_dev {int /*<<< orphan*/  dev; } ;
struct icy_i2c {int /*<<< orphan*/  adapter; int /*<<< orphan*/  ltc2990_fwnode; int /*<<< orphan*/  ltc2990_client; } ;

/* Variables and functions */
 struct icy_i2c* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwnode_remove_software_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icy_remove(struct zorro_dev *z)
{
	struct icy_i2c *i2c = dev_get_drvdata(&z->dev);

	i2c_unregister_device(i2c->ltc2990_client);
	fwnode_remove_software_node(i2c->ltc2990_fwnode);

	i2c_del_adapter(&i2c->adapter);
}