#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct stm32_fmc2_nfc {scalar_t__ io_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ FMC2_BCHDSR0 ; 
 scalar_t__ FMC2_BCHDSR1 ; 
 scalar_t__ FMC2_BCHDSR2 ; 
 scalar_t__ FMC2_BCHDSR3 ; 
 scalar_t__ FMC2_BCHDSR4 ; 
 int /*<<< orphan*/  FMC2_TIMEOUT_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int stm32_fmc2_bch_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_fmc2_disable_bch_irq (struct stm32_fmc2_nfc*) ; 
 int /*<<< orphan*/  stm32_fmc2_set_ecc (struct stm32_fmc2_nfc*,int) ; 
 struct stm32_fmc2_nfc* to_stm32_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_fmc2_bch_correct(struct nand_chip *chip, u8 *dat,
				  u8 *read_ecc, u8 *calc_ecc)
{
	struct stm32_fmc2_nfc *fmc2 = to_stm32_nfc(chip->controller);
	u32 ecc_sta[5];

	/* Wait until the decoding error is ready */
	if (!wait_for_completion_timeout(&fmc2->complete,
					 msecs_to_jiffies(FMC2_TIMEOUT_MS))) {
		dev_err(fmc2->dev, "bch timeout\n");
		stm32_fmc2_disable_bch_irq(fmc2);
		return -ETIMEDOUT;
	}

	ecc_sta[0] = readl_relaxed(fmc2->io_base + FMC2_BCHDSR0);
	ecc_sta[1] = readl_relaxed(fmc2->io_base + FMC2_BCHDSR1);
	ecc_sta[2] = readl_relaxed(fmc2->io_base + FMC2_BCHDSR2);
	ecc_sta[3] = readl_relaxed(fmc2->io_base + FMC2_BCHDSR3);
	ecc_sta[4] = readl_relaxed(fmc2->io_base + FMC2_BCHDSR4);

	/* Disable ECC */
	stm32_fmc2_set_ecc(fmc2, false);

	return stm32_fmc2_bch_decode(chip->ecc.size, dat, ecc_sta);
}