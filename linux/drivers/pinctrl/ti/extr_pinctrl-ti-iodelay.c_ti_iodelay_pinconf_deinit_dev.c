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
struct ti_iodelay_reg_data {int /*<<< orphan*/  global_lock_val; int /*<<< orphan*/  global_lock_mask; int /*<<< orphan*/  reg_global_lock_offset; } ;
struct ti_iodelay_device {int /*<<< orphan*/  regmap; struct ti_iodelay_reg_data* reg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_iodelay_pinconf_deinit_dev(struct ti_iodelay_device *iod)
{
	const struct ti_iodelay_reg_data *reg = iod->reg_data;

	/* lock the iodelay region back again */
	regmap_update_bits(iod->regmap, reg->reg_global_lock_offset,
			   reg->global_lock_mask, reg->global_lock_val);
}