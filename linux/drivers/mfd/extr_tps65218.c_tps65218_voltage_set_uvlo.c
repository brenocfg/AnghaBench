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
 int TPS65218_CONFIG1_UVLO_2750000 ; 
 int TPS65218_CONFIG1_UVLO_2950000 ; 
 int TPS65218_CONFIG1_UVLO_3250000 ; 
 int TPS65218_CONFIG1_UVLO_3350000 ; 
 int /*<<< orphan*/  TPS65218_CONFIG1_UVLO_MASK ; 
 int /*<<< orphan*/  TPS65218_PROTECT_L1 ; 
 int /*<<< orphan*/  TPS65218_REG_CONFIG1 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  tps65218_update_bits (struct tps65218*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65218_voltage_set_uvlo(struct tps65218 *tps)
{
	u32 uvlo;
	int uvloval;

	if (of_property_read_u32(tps->dev->of_node,
				 "ti,under-voltage-limit-microvolt", &uvlo))
		return 0;

	switch (uvlo) {
	case 2750000:
		uvloval = TPS65218_CONFIG1_UVLO_2750000;
		break;
	case 2950000:
		uvloval = TPS65218_CONFIG1_UVLO_2950000;
		break;
	case 3250000:
		uvloval = TPS65218_CONFIG1_UVLO_3250000;
		break;
	case 3350000:
		uvloval = TPS65218_CONFIG1_UVLO_3350000;
		break;
	default:
		dev_err(tps->dev,
			"Invalid ti,under-voltage-limit-microvolt value\n");
		return -EINVAL;
	}

	tps65218_update_bits(tps, TPS65218_REG_CONFIG1,
			     TPS65218_CONFIG1_UVLO_MASK, uvloval,
			     TPS65218_PROTECT_L1);
	return 0;
}