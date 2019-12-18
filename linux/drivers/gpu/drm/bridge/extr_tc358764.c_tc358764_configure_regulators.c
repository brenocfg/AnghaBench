#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tc358764 {int /*<<< orphan*/  dev; TYPE_1__* supplies; } ;
struct TYPE_3__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * tc358764_supplies ; 

__attribute__((used)) static int tc358764_configure_regulators(struct tc358764 *ctx)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(ctx->supplies); ++i)
		ctx->supplies[i].supply = tc358764_supplies[i];

	ret = devm_regulator_bulk_get(ctx->dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0)
		dev_err(ctx->dev, "failed to get regulators: %d\n", ret);

	return ret;
}