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
 size_t I2C_IDX_RX_P0 ; 
 size_t I2C_IDX_TX_P2 ; 
 int SP_CKDT_CHG ; 
 int /*<<< orphan*/  SP_COMMON_INT_MASK4_REG ; 
 int /*<<< orphan*/  SP_DP_INT_MASK1_REG ; 
 int SP_HPD_LOST ; 
 int SP_HPD_PLUG ; 
 int /*<<< orphan*/  SP_INT_CTRL_REG ; 
 int /*<<< orphan*/  SP_INT_MASK1_REG ; 
 int SP_SCDT_CHG ; 
 int SP_TRAINING_FINISH ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int anx78xx_enable_interrupts(struct anx78xx *anx78xx)
{
	int err;

	/*
	 * BIT0: INT pin assertion polarity: 1 = assert high
	 * BIT1: INT pin output type: 0 = push/pull
	 */
	err = regmap_write(anx78xx->map[I2C_IDX_TX_P2], SP_INT_CTRL_REG, 0x01);
	if (err)
		return err;

	err = regmap_write(anx78xx->map[I2C_IDX_TX_P2],
			   SP_COMMON_INT_MASK4_REG, SP_HPD_LOST | SP_HPD_PLUG);
	if (err)
		return err;

	err = regmap_write(anx78xx->map[I2C_IDX_TX_P2], SP_DP_INT_MASK1_REG,
			   SP_TRAINING_FINISH);
	if (err)
		return err;

	err = regmap_write(anx78xx->map[I2C_IDX_RX_P0], SP_INT_MASK1_REG,
			   SP_CKDT_CHG | SP_SCDT_CHG);
	if (err)
		return err;

	return 0;
}