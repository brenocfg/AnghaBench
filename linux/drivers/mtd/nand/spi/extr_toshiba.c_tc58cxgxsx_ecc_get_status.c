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
typedef  int u8 ;
struct spinand_device {int /*<<< orphan*/  spimem; } ;
struct spi_mem_op {int dummy; } ;
struct TYPE_2__ {int strength; } ;
struct nand_device {TYPE_1__ eccreq; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 struct spi_mem_op SPINAND_GET_FEATURE_OP (int,int*) ; 
#define  STATUS_ECC_HAS_BITFLIPS 131 
 int STATUS_ECC_MASK ; 
#define  STATUS_ECC_NO_BITFLIPS 130 
#define  STATUS_ECC_UNCOR_ERROR 129 
#define  TOSH_STATUS_ECC_HAS_BITFLIPS_T 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  spi_mem_exec_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 

__attribute__((used)) static int tc58cxgxsx_ecc_get_status(struct spinand_device *spinand,
				      u8 status)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	u8 mbf = 0;
	struct spi_mem_op op = SPINAND_GET_FEATURE_OP(0x30, &mbf);

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	case STATUS_ECC_HAS_BITFLIPS:
	case TOSH_STATUS_ECC_HAS_BITFLIPS_T:
		/*
		 * Let's try to retrieve the real maximum number of bitflips
		 * in order to avoid forcing the wear-leveling layer to move
		 * data around if it's not necessary.
		 */
		if (spi_mem_exec_op(spinand->spimem, &op))
			return nand->eccreq.strength;

		mbf >>= 4;

		if (WARN_ON(mbf > nand->eccreq.strength || !mbf))
			return nand->eccreq.strength;

		return mbf;

	default:
		break;
	}

	return -EINVAL;
}