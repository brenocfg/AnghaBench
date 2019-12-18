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
typedef  int u32 ;
struct tps65218 {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TPS65218_CONFIG1_STRICT ; 
 int /*<<< orphan*/  TPS65218_PROTECT_L1 ; 
 int /*<<< orphan*/  TPS65218_REG_CONFIG1 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  tps65218_update_bits (struct tps65218*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65218_voltage_set_strict(struct tps65218 *tps)
{
	u32 strict;

	if (of_property_read_u32(tps->dev->of_node,
				 "ti,strict-supply-voltage-supervision",
				 &strict))
		return 0;

	if (strict != 0 && strict != 1) {
		dev_err(tps->dev,
			"Invalid ti,strict-supply-voltage-supervision value\n");
		return -EINVAL;
	}

	tps65218_update_bits(tps, TPS65218_REG_CONFIG1,
			     TPS65218_CONFIG1_STRICT,
			     strict ? TPS65218_CONFIG1_STRICT : 0,
			     TPS65218_PROTECT_L1);
	return 0;
}