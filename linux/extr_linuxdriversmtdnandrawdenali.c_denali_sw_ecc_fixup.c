#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {unsigned int corrected; } ;
struct mtd_info {TYPE_3__ ecc_stats; } ;
struct TYPE_4__ {unsigned int size; } ;
struct TYPE_5__ {TYPE_1__ ecc; } ;
struct denali_nand_info {unsigned int devs_per_cs; scalar_t__ reg; TYPE_2__ nand; } ;

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
 int /*<<< orphan*/  denali_reset_irq (struct denali_nand_info*) ; 
 int denali_wait_for_irq (struct denali_nand_info*,int) ; 
 unsigned int hweight8 (int) ; 
 int ioread32 (scalar_t__) ; 
 unsigned int max (unsigned int,unsigned int) ; 

__attribute__((used)) static int denali_sw_ecc_fixup(struct mtd_info *mtd,
			       struct denali_nand_info *denali,
			       unsigned long *uncor_ecc_flags, uint8_t *buf)
{
	unsigned int ecc_size = denali->nand.ecc.size;
	unsigned int bitflips = 0;
	unsigned int max_bitflips = 0;
	uint32_t err_addr, err_cor_info;
	unsigned int err_byte, err_sector, err_device;
	uint8_t err_cor_value;
	unsigned int prev_sector = 0;
	uint32_t irq_status;

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
			mtd->ecc_stats.corrected += flips_in_byte;
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