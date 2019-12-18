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
struct spinand_device {int dummy; } ;
struct TYPE_2__ {int strength; } ;
struct nand_device {TYPE_1__ eccreq; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
#define  STATUS_ECC_HAS_BITFLIPS 130 
 int STATUS_ECC_MASK ; 
#define  STATUS_ECC_NO_BITFLIPS 129 
#define  STATUS_ECC_UNCOR_ERROR 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mx35lf1ge4ab_get_eccsr (struct spinand_device*,int*) ; 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 

__attribute__((used)) static int mx35lf1ge4ab_ecc_get_status(struct spinand_device *spinand,
				       u8 status)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	u8 eccsr;

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	case STATUS_ECC_HAS_BITFLIPS:
		/*
		 * Let's try to retrieve the real maximum number of bitflips
		 * in order to avoid forcing the wear-leveling layer to move
		 * data around if it's not necessary.
		 */
		if (mx35lf1ge4ab_get_eccsr(spinand, &eccsr))
			return nand->eccreq.strength;

		if (WARN_ON(eccsr > nand->eccreq.strength || !eccsr))
			return nand->eccreq.strength;

		return eccsr;

	default:
		break;
	}

	return -EINVAL;
}