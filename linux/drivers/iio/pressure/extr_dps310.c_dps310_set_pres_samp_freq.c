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
typedef  int u8 ;
struct dps310_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPS310_PRS_CFG ; 
 int /*<<< orphan*/  DPS310_PRS_RATE_BITS ; 
 int EINVAL ; 
 int ilog2 (int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dps310_set_pres_samp_freq(struct dps310_data *data, int freq)
{
	u8 val;

	if (freq < 0 || freq > 128)
		return -EINVAL;

	val = ilog2(freq) << 4;

	return regmap_update_bits(data->regmap, DPS310_PRS_CFG,
				  DPS310_PRS_RATE_BITS, val);
}