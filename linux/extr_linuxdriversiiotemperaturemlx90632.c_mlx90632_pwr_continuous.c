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
struct regmap {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX90632_CFG_PWR_MASK ; 
 int /*<<< orphan*/  MLX90632_PWR_STATUS_CONTINUOUS ; 
 int /*<<< orphan*/  MLX90632_REG_CONTROL ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 mlx90632_pwr_continuous(struct regmap *regmap)
{
	return regmap_update_bits(regmap, MLX90632_REG_CONTROL,
				  MLX90632_CFG_PWR_MASK,
				  MLX90632_PWR_STATUS_CONTINUOUS);
}