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
struct anx78xx {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 size_t I2C_IDX_TX_P0 ; 
 unsigned int SP_AUX_EN ; 
 int /*<<< orphan*/  SP_DP_AUX_CH_CTRL2_REG ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static bool anx78xx_aux_op_finished(struct anx78xx *anx78xx)
{
	unsigned int value;
	int err;

	err = regmap_read(anx78xx->map[I2C_IDX_TX_P0], SP_DP_AUX_CH_CTRL2_REG,
			  &value);
	if (err < 0)
		return false;

	return (value & SP_AUX_EN) == 0;
}