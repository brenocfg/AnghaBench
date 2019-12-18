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
struct ov5695 {TYPE_2__* supplies; TYPE_1__* client; } ;
struct TYPE_4__ {int /*<<< orphan*/  supply; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int OV5695_NUM_SUPPLIES ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/ * ov5695_supply_names ; 

__attribute__((used)) static int ov5695_configure_regulators(struct ov5695 *ov5695)
{
	int i;

	for (i = 0; i < OV5695_NUM_SUPPLIES; i++)
		ov5695->supplies[i].supply = ov5695_supply_names[i];

	return devm_regulator_bulk_get(&ov5695->client->dev,
				       OV5695_NUM_SUPPLIES,
				       ov5695->supplies);
}