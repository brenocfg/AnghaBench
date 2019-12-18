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
typedef  int /*<<< orphan*/  u8 ;
struct vcnl4035_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCNL4035_ALS_CONF ; 
 int /*<<< orphan*/  VCNL4035_MODE_ALS_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vcnl4035_set_als_power_state(struct vcnl4035_data *data, u8 status)
{
	return regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
					VCNL4035_MODE_ALS_MASK,
					status);
}