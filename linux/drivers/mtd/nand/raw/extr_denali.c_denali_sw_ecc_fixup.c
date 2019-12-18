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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {unsigned int size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_ecc_stats {unsigned int corrected; } ;
struct denali_controller {unsigned int devs_per_cs; scalar_t__ reg; } ;
struct TYPE_4__ {struct mtd_ecc_stats ecc_stats; } ;

/* Variables and functions */
 unsigned long BIT (unsigned int) ; 
 scalar_t__ ECC_ERROR_ADDRESS ; 
 int /*<<< orphan*/  ECC_ERROR_ADDRESS__OFFSET ; 
 int /*<<< orphan*/  ECC_ERROR_ADDRESS__SECTOR ; 
 int EIO ; 
 scalar_t__ ERR_CORRECTION_INFO ; 
 int /*<<< orphan*/  ERR_CORRECTION_INFO__BYTE ; 
 int /*<<< orphan*/  ERR_CORRECTION_INFO__DEVICE ; 
 int ERR_CORRECTION_INFO__LAST_ERR ; 
 int ERR_CORRECTION_INFO__UNCOR ; 
 void* FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int INTR__ECC_TRANSACTION_DONE ; 
 int /*<<< orphan*/  denali_reset_irq (struct denali_controller*) ; 
 int denali_wait_for_irq (struct denali_controller*,int) ; 
 unsigned int hweight8 (int) ; 
 int ioread32 (scalar_t__) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 TYPE_2__* nand_to_mtd (struct nand_chip*) ; 
 struct denali_controller* to_denali_controller (struct nand_chip*) ; 

__attribute__((used)) static int denali_sw_ecc_fixup(struct nand_chip *chip,
			       unsigned long *uncor_ecc_flags, u8 *buf)
{
	struct denali_controller *denali = to_denali_controller(chip);
	struct mtd_ecc_stats *ecc_stats = &nand_to_mtd(chip)->ecc_stats;
	unsigned int ecc_size = chip->ecc.size;
	unsigned int bitflips = 0;
	unsigned int max_bitflips = 0;
	u32 err_addr, err_cor_info;
	unsigned int err_byte, err_sector, err_device;
	u8 err_cor_value;
	unsigned int prev_sector = 0;
	u32 irq_status;

	denali_reset_irq(denali);

	do {
		err_addr = ioread32(denali->reg + ECC_ERROR_ADDRESS);
		err_sector = FIELD_GET(ECC_ERROR_ADDRESS__SECTOR, err_addr);
		err_byte = FIELD_GET(ECC_ERROR_ADDRESS__OFFSET, err_addr);

		err_cor_info = ioread32(denali->reg + ERR_CORRECTION_INFO);
		err_cor_value = FIELD_GET(ERR_CORRECTION_INFO__BYTE,
					  err_cor_info);
		err_device = FIELD_GET(ERR_CORRECTION_INFO__DEVICE,
				       err_cor_info);

		/* reset the bitflip counter when crossing ECC sector */
		if (err_sector != prev_sector)
			bitflips = 0;

		if (err_cor_info & ERR_CORRECTION_INFO__UNCOR) {
			/*
			 * Check later if this is a real ECC error, or
			 * an erased sector.
			 */
			*uncor_ecc_flags |= BIT(err_sector);
		} else if (err_byte < ecc_size) {
			/*
			 * If err_byte is larger than ecc_size, means error
			 * happened in OOB, so we ignore it. It's no need for
			 * us to correct it err_device is represented the NAND
			 * error bits are happened in if there are more than
			 * one NAND connected.
			 */
			int offset;
			unsigned int flips_in_byte;

			offset = (err_sector * ecc_size + err_byte) *
					denali->devs_per_cs + err_device;

			/* correct the ECC error */
			flips_in_byte = hweight8(buf[offset] ^ err_cor_value);
			buf[offset] ^= err_cor_value;
			ecc_stats->corrected += flips_in_byte;
			bitflips += flips_in_byte;

			max_bitflips = max(max_bitflips, bitflips);
		}

		prev_sector = err_sector;
	} while (!(err_cor_info & ERR_CORRECTION_INFO__LAST_ERR));

	/*
	 * Once handle all ECC errors, controller will trigger an
	 * ECC_TRANSACTION_DONE interrupt.
	 */
	irq_status = denali_wait_for_irq(denali, INTR__ECC_TRANSACTION_DONE);
	if (!(irq_status & INTR__ECC_TRANSACTION_DONE))
		return -EIO;

	return max_bitflips;
}