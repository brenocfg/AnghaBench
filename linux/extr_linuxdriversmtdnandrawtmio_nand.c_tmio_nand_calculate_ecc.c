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
typedef  unsigned int u_char ;
struct tmio_nand {scalar_t__ fcr; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ FCR_DATA ; 
 scalar_t__ FCR_MODE ; 
 int /*<<< orphan*/  FCR_MODE_DATA ; 
 int /*<<< orphan*/  FCR_MODE_HWECC_RESULT ; 
 struct tmio_nand* mtd_to_tmio (struct mtd_info*) ; 
 unsigned int tmio_ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tmio_nand_calculate_ecc(struct mtd_info *mtd, const u_char *dat,
							u_char *ecc_code)
{
	struct tmio_nand *tmio = mtd_to_tmio(mtd);
	unsigned int ecc;

	tmio_iowrite8(FCR_MODE_HWECC_RESULT, tmio->fcr + FCR_MODE);

	ecc = tmio_ioread16(tmio->fcr + FCR_DATA);
	ecc_code[1] = ecc;	/* 000-255 LP7-0 */
	ecc_code[0] = ecc >> 8;	/* 000-255 LP15-8 */
	ecc = tmio_ioread16(tmio->fcr + FCR_DATA);
	ecc_code[2] = ecc;	/* 000-255 CP5-0,11b */
	ecc_code[4] = ecc >> 8;	/* 256-511 LP7-0 */
	ecc = tmio_ioread16(tmio->fcr + FCR_DATA);
	ecc_code[3] = ecc;	/* 256-511 LP15-8 */
	ecc_code[5] = ecc >> 8;	/* 256-511 CP5-0,11b */

	tmio_iowrite8(FCR_MODE_DATA, tmio->fcr + FCR_MODE);
	return 0;
}