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
struct mipid02_dev {TYPE_2__* supplies; TYPE_1__* i2c_client; } ;
struct TYPE_4__ {int /*<<< orphan*/  supply; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int MIPID02_NUM_SUPPLIES ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,unsigned int,TYPE_2__*) ; 
 int /*<<< orphan*/ * mipid02_supply_name ; 

__attribute__((used)) static int mipid02_get_regulators(struct mipid02_dev *bridge)
{
	unsigned int i;

	for (i = 0; i < MIPID02_NUM_SUPPLIES; i++)
		bridge->supplies[i].supply = mipid02_supply_name[i];

	return devm_regulator_bulk_get(&bridge->i2c_client->dev,
				       MIPID02_NUM_SUPPLIES,
				       bridge->supplies);
}