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
typedef  scalar_t__ u32 ;
struct ltc4306 {int /*<<< orphan*/  regmap; } ;
struct i2c_mux_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int /*<<< orphan*/  LTC_REG_SWITCH ; 
 int /*<<< orphan*/  LTC_SWITCH_MASK ; 
 struct ltc4306* i2c_mux_priv (struct i2c_mux_core*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc4306_select_mux(struct i2c_mux_core *muxc, u32 chan)
{
	struct ltc4306 *data = i2c_mux_priv(muxc);

	return regmap_update_bits(data->regmap, LTC_REG_SWITCH,
				  LTC_SWITCH_MASK, BIT(7 - chan));
}