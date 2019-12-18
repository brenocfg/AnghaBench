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
typedef  int u32 ;
struct TYPE_2__ {int bytes; int size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct fsmc_nand_data {scalar_t__ regs_va; } ;

/* Variables and functions */
 int EBADMSG ; 
 scalar_t__ ECC1 ; 
 scalar_t__ ECC2 ; 
 scalar_t__ ECC3 ; 
 scalar_t__ STS ; 
 int /*<<< orphan*/  change_bit (int,unsigned long*) ; 
 int count_written_bits (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 struct fsmc_nand_data* nand_to_fsmc (struct nand_chip*) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int fsmc_bch8_correct_data(struct nand_chip *chip, u8 *dat,
				  u8 *read_ecc, u8 *calc_ecc)
{
	struct fsmc_nand_data *host = nand_to_fsmc(chip);
	u32 err_idx[8];
	u32 num_err, i;
	u32 ecc1, ecc2, ecc3, ecc4;

	num_err = (readl_relaxed(host->regs_va + STS) >> 10) & 0xF;

	/* no bit flipping */
	if (likely(num_err == 0))
		return 0;

	/* too many errors */
	if (unlikely(num_err > 8)) {
		/*
		 * This is a temporary erase check. A newly erased page read
		 * would result in an ecc error because the oob data is also
		 * erased to FF and the calculated ecc for an FF data is not
		 * FF..FF.
		 * This is a workaround to skip performing correction in case
		 * data is FF..FF
		 *
		 * Logic:
		 * For every page, each bit written as 0 is counted until these
		 * number of bits are greater than 8 (the maximum correction
		 * capability of FSMC for each 512 + 13 bytes)
		 */

		int bits_ecc = count_written_bits(read_ecc, chip->ecc.bytes, 8);
		int bits_data = count_written_bits(dat, chip->ecc.size, 8);

		if ((bits_ecc + bits_data) <= 8) {
			if (bits_data)
				memset(dat, 0xff, chip->ecc.size);
			return bits_data;
		}

		return -EBADMSG;
	}

	/*
	 * ------------------- calc_ecc[] bit wise -----------|--13 bits--|
	 * |---idx[7]--|--.....-----|---idx[2]--||---idx[1]--||---idx[0]--|
	 *
	 * calc_ecc is a 104 bit information containing maximum of 8 error
	 * offset information of 13 bits each. calc_ecc is copied into a
	 * u64 array and error offset indexes are populated in err_idx
	 * array
	 */
	ecc1 = readl_relaxed(host->regs_va + ECC1);
	ecc2 = readl_relaxed(host->regs_va + ECC2);
	ecc3 = readl_relaxed(host->regs_va + ECC3);
	ecc4 = readl_relaxed(host->regs_va + STS);

	err_idx[0] = (ecc1 >> 0) & 0x1FFF;
	err_idx[1] = (ecc1 >> 13) & 0x1FFF;
	err_idx[2] = (((ecc2 >> 0) & 0x7F) << 6) | ((ecc1 >> 26) & 0x3F);
	err_idx[3] = (ecc2 >> 7) & 0x1FFF;
	err_idx[4] = (((ecc3 >> 0) & 0x1) << 12) | ((ecc2 >> 20) & 0xFFF);
	err_idx[5] = (ecc3 >> 1) & 0x1FFF;
	err_idx[6] = (ecc3 >> 14) & 0x1FFF;
	err_idx[7] = (((ecc4 >> 16) & 0xFF) << 5) | ((ecc3 >> 27) & 0x1F);

	i = 0;
	while (num_err--) {
		change_bit(0, (unsigned long *)&err_idx[i]);
		change_bit(1, (unsigned long *)&err_idx[i]);

		if (err_idx[i] < chip->ecc.size * 8) {
			change_bit(err_idx[i], (unsigned long *)dat);
			i++;
		}
	}
	return i;
}