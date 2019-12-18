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
typedef  int u32 ;
struct stm32_fmc2_nfc {scalar_t__ io_base; int /*<<< orphan*/  dev; } ;
struct nand_chip {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 scalar_t__ FMC2_HECCR ; 
 scalar_t__ FMC2_SR ; 
 int FMC2_SR_NWRF ; 
 int /*<<< orphan*/  FMC2_TIMEOUT_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_fmc2_ham_set_ecc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_fmc2_set_ecc (struct stm32_fmc2_nfc*,int) ; 
 struct stm32_fmc2_nfc* to_stm32_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_fmc2_ham_calculate(struct nand_chip *chip, const u8 *data,
				    u8 *ecc)
{
	struct stm32_fmc2_nfc *fmc2 = to_stm32_nfc(chip->controller);
	u32 sr, heccr;
	int ret;

	ret = readl_relaxed_poll_timeout(fmc2->io_base + FMC2_SR,
					 sr, sr & FMC2_SR_NWRF, 10,
					 FMC2_TIMEOUT_MS);
	if (ret) {
		dev_err(fmc2->dev, "ham timeout\n");
		return ret;
	}

	heccr = readl_relaxed(fmc2->io_base + FMC2_HECCR);

	stm32_fmc2_ham_set_ecc(heccr, ecc);

	/* Disable ECC */
	stm32_fmc2_set_ecc(fmc2, false);

	return 0;
}