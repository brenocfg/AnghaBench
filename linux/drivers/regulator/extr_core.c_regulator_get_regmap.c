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
struct regulator {TYPE_1__* rdev; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct regmap* ERR_PTR (int /*<<< orphan*/ ) ; 

struct regmap *regulator_get_regmap(struct regulator *regulator)
{
	struct regmap *map = regulator->rdev->regmap;

	return map ? map : ERR_PTR(-EOPNOTSUPP);
}