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
 int /*<<< orphan*/  SP_AUX_ADDR_15_8_REG ; 
 int /*<<< orphan*/  SP_AUX_ADDR_19_16_MASK ; 
 int /*<<< orphan*/  SP_AUX_ADDR_19_16_REG ; 
 int /*<<< orphan*/  SP_AUX_ADDR_7_0_REG ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int anx78xx_aux_address(struct anx78xx *anx78xx, unsigned int addr)
{
	int err;

	err = regmap_write(anx78xx->map[I2C_IDX_TX_P0], SP_AUX_ADDR_7_0_REG,
			   addr & 0xff);
	if (err)
		return err;

	err = regmap_write(anx78xx->map[I2C_IDX_TX_P0], SP_AUX_ADDR_15_8_REG,
			   (addr & 0xff00) >> 8);
	if (err)
		return err;

	/*
	 * DP AUX CH Address Register #2, only update bits[3:0]
	 * [7:4] RESERVED
	 * [3:0] AUX_ADDR[19:16], Register control AUX CH address.
	 */
	err = regmap_update_bits(anx78xx->map[I2C_IDX_TX_P0],
				 SP_AUX_ADDR_19_16_REG,
				 SP_AUX_ADDR_19_16_MASK,
				 (addr & 0xf0000) >> 16);

	if (err)
		return err;

	return 0;
}