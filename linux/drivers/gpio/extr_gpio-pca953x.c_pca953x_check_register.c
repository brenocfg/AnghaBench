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
typedef  int u32 ;
struct pca953x_chip {int driver_data; } ;

/* Variables and functions */
 int BIT (int) ; 
 int NBANK (struct pca953x_chip*) ; 
 int PCA_PCAL ; 
 unsigned int REG_ADDR_EXT ; 
 unsigned int REG_ADDR_MASK ; 
 int pca953x_bank_shift (struct pca953x_chip*) ; 

__attribute__((used)) static bool pca953x_check_register(struct pca953x_chip *chip, unsigned int reg,
				   u32 checkbank)
{
	int bank_shift = pca953x_bank_shift(chip);
	int bank = (reg & REG_ADDR_MASK) >> bank_shift;
	int offset = reg & (BIT(bank_shift) - 1);

	/* Special PCAL extended register check. */
	if (reg & REG_ADDR_EXT) {
		if (!(chip->driver_data & PCA_PCAL))
			return false;
		bank += 8;
	}

	/* Register is not in the matching bank. */
	if (!(BIT(bank) & checkbank))
		return false;

	/* Register is not within allowed range of bank. */
	if (offset >= NBANK(chip))
		return false;

	return true;
}