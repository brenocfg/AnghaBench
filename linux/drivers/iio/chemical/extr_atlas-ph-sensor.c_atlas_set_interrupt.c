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
struct atlas_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATLAS_REG_INT_CONTROL ; 
 int /*<<< orphan*/  ATLAS_REG_INT_CONTROL_EN ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atlas_set_interrupt(struct atlas_data *data, bool state)
{
	return regmap_update_bits(data->regmap, ATLAS_REG_INT_CONTROL,
				  ATLAS_REG_INT_CONTROL_EN,
				  state ? ATLAS_REG_INT_CONTROL_EN : 0);
}