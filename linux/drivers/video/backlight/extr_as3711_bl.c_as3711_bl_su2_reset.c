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
struct as3711_bl_supply {TYPE_1__* pdata; struct as3711* as3711; } ;
struct as3711 {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int su2_fbprot; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3711_STEPUP_CONTROL_2 ; 
 int /*<<< orphan*/  AS3711_STEPUP_CONTROL_5 ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int as3711_bl_su2_reset(struct as3711_bl_supply *supply)
{
	struct as3711 *as3711 = supply->as3711;
	int ret = regmap_update_bits(as3711->regmap, AS3711_STEPUP_CONTROL_5,
				     3, supply->pdata->su2_fbprot);
	if (!ret)
		ret = regmap_update_bits(as3711->regmap,
					 AS3711_STEPUP_CONTROL_2, 1, 0);
	if (!ret)
		ret = regmap_update_bits(as3711->regmap,
					 AS3711_STEPUP_CONTROL_2, 1, 1);
	return ret;
}