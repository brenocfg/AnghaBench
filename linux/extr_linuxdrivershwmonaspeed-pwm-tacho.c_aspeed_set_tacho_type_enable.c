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
typedef  size_t u8 ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_CTRL_FAN_TYPE_EN ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* type_params ; 

__attribute__((used)) static void aspeed_set_tacho_type_enable(struct regmap *regmap, u8 type,
					 bool enable)
{
	regmap_update_bits(regmap, type_params[type].ctrl_reg,
			   TYPE_CTRL_FAN_TYPE_EN,
			   enable ? TYPE_CTRL_FAN_TYPE_EN : 0);
}