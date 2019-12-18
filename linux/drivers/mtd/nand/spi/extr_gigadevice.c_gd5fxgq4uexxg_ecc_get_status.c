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
typedef  int u8 ;
struct spinand_device {int /*<<< orphan*/  spimem; } ;
struct spi_mem_op {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int /*<<< orphan*/  GD5FXGQ4UEXXG_REG_STATUS2 ; 
#define  GD5FXGQ4XA_STATUS_ECC_1_7_BITFLIPS 131 
#define  GD5FXGQ4XA_STATUS_ECC_8_BITFLIPS 130 
 struct spi_mem_op SPINAND_GET_FEATURE_OP (int /*<<< orphan*/ ,int*) ; 
 int STATUS_ECC_MASK ; 
#define  STATUS_ECC_NO_BITFLIPS 129 
#define  STATUS_ECC_UNCOR_ERROR 128 
 int spi_mem_exec_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 

__attribute__((used)) static int gd5fxgq4uexxg_ecc_get_status(struct spinand_device *spinand,
					u8 status)
{
	u8 status2;
	struct spi_mem_op op = SPINAND_GET_FEATURE_OP(GD5FXGQ4UEXXG_REG_STATUS2,
						      &status2);
	int ret;

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case GD5FXGQ4XA_STATUS_ECC_1_7_BITFLIPS:
		/*
		 * Read status2 register to determine a more fine grained
		 * bit error status
		 */
		ret = spi_mem_exec_op(spinand->spimem, &op);
		if (ret)
			return ret;

		/*
		 * 4 ... 7 bits are flipped (1..4 can't be detected, so
		 * report the maximum of 4 in this case
		 */
		/* bits sorted this way (3...0): ECCS1,ECCS0,ECCSE1,ECCSE0 */
		return ((status & STATUS_ECC_MASK) >> 2) |
			((status2 & STATUS_ECC_MASK) >> 4);

	case GD5FXGQ4XA_STATUS_ECC_8_BITFLIPS:
		return 8;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	default:
		break;
	}

	return -EINVAL;
}