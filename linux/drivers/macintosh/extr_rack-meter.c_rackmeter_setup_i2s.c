#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rackmeter {scalar_t__ i2s_regs; int /*<<< orphan*/ * i2s; TYPE_2__* mdev; } ;
struct macio_chip {int dummy; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {struct macio_chip* chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYLARGO_FCR1 ; 
 int KL1_I2S0_CELL_ENABLE ; 
 int KL1_I2S0_CLK_ENABLE_BIT ; 
 int KL1_I2S0_ENABLE ; 
 int /*<<< orphan*/  MACIO_BIC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MACIO_BIS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MACIO_IN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAC_FTR_SOUND_CHIP_ENABLE ; 
 int /*<<< orphan*/  PMAC_FTR_WRITE_GPIO ; 
 int /*<<< orphan*/  RACKMETER_MAGIC_GPIO ; 
 int /*<<< orphan*/  in_le32 (scalar_t__) ; 
 int /*<<< orphan*/  out_le32 (scalar_t__,int) ; 
 int /*<<< orphan*/  pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rackmeter_setup_i2s(struct rackmeter *rm)
{
	struct macio_chip *macio = rm->mdev->bus->chip;

	/* First whack magic GPIO */
	pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, RACKMETER_MAGIC_GPIO, 5);


	/* Call feature code to enable the sound channel and the proper
	 * clock sources
	 */
	pmac_call_feature(PMAC_FTR_SOUND_CHIP_ENABLE, rm->i2s, 0, 1);

	/* Power i2s and stop i2s clock. We whack MacIO FCRs directly for now.
	 * This is a bit racy, thus we should add new platform functions to
	 * handle that. snd-aoa needs that too
	 */
	MACIO_BIS(KEYLARGO_FCR1, KL1_I2S0_ENABLE);
	MACIO_BIC(KEYLARGO_FCR1, KL1_I2S0_CLK_ENABLE_BIT);
	(void)MACIO_IN32(KEYLARGO_FCR1);
	udelay(10);

	/* Then setup i2s. For now, we use the same magic value that
	 * the OS X driver seems to use. We might want to play around
	 * with the clock divisors later
	 */
	out_le32(rm->i2s_regs + 0x10, 0x01fa0000);
	(void)in_le32(rm->i2s_regs + 0x10);
	udelay(10);

	/* Fully restart i2s*/
	MACIO_BIS(KEYLARGO_FCR1, KL1_I2S0_CELL_ENABLE |
		  KL1_I2S0_CLK_ENABLE_BIT);
	(void)MACIO_IN32(KEYLARGO_FCR1);
	udelay(10);
}