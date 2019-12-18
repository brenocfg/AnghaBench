#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct encx24j600_context {void* phymap; void* regmap; int /*<<< orphan*/  mutex; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct encx24j600_context* lock_arg; } ;

/* Variables and functions */
 void* devm_regmap_init (struct device*,int /*<<< orphan*/ *,struct encx24j600_context*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ phycfg ; 
 int /*<<< orphan*/  phymap_encx24j600 ; 
 TYPE_1__ regcfg ; 
 int /*<<< orphan*/  regmap_encx24j600 ; 

void devm_regmap_init_encx24j600(struct device *dev,
				 struct encx24j600_context *ctx)
{
	mutex_init(&ctx->mutex);
	regcfg.lock_arg = ctx;
	ctx->regmap = devm_regmap_init(dev, &regmap_encx24j600, ctx, &regcfg);
	ctx->phymap = devm_regmap_init(dev, &phymap_encx24j600, ctx, &phycfg);
}