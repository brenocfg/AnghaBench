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
 int /*<<< orphan*/  TPS65218_CONFIG2_UVLOHYS ; 
 int /*<<< orphan*/  TPS65218_PROTECT_L1 ; 
 int /*<<< orphan*/  TPS65218_REG_CONFIG2 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  tps65218_update_bits (struct tps65218*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65218_voltage_set_uv_hyst(struct tps65218 *tps)
{
	u32 hyst;

	if (of_property_read_u32(tps->dev->of_node,
				 "ti,under-voltage-hyst-microvolt", &hyst))
		return 0;

	if (hyst != 400000 && hyst != 200000) {
		dev_err(tps->dev,
			"Invalid ti,under-voltage-hyst-microvolt value\n");
		return -EINVAL;
	}

	tps65218_update_bits(tps, TPS65218_REG_CONFIG2,
			     TPS65218_CONFIG2_UVLOHYS,
			     hyst == 400000 ? TPS65218_CONFIG2_UVLOHYS : 0,
			     TPS65218_PROTECT_L1);
	return 0;
}