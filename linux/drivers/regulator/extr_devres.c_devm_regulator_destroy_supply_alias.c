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
struct regulator_supply_alias_match {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_unregister_supply_alias (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devm_regulator_destroy_supply_alias(struct device *dev, void *res)
{
	struct regulator_supply_alias_match *match = res;

	regulator_unregister_supply_alias(match->dev, match->id);
}