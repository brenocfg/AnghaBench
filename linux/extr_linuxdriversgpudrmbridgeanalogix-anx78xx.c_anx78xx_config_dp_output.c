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
 size_t I2C_IDX_TX_P2 ; 
 int /*<<< orphan*/  SP_VIDEO_EN ; 
 int /*<<< orphan*/  SP_VIDEO_MUTE ; 
 int /*<<< orphan*/  SP_VID_CTRL1_REG ; 
 int anx78xx_clear_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int anx78xx_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int anx78xx_config_dp_output(struct anx78xx *anx78xx)
{
	int err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTRL1_REG,
				 SP_VIDEO_MUTE);
	if (err)
		return err;

	/* Enable DP output */
	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTRL1_REG,
			       SP_VIDEO_EN);
	if (err)
		return err;

	return 0;
}