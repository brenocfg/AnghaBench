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
struct TYPE_3__ {int (* get_status ) (struct spinand_device*,int) ;} ;
struct spinand_device {TYPE_1__ eccinfo; } ;
struct TYPE_4__ {int strength; } ;
struct nand_device {TYPE_2__ eccreq; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
#define  STATUS_ECC_HAS_BITFLIPS 130 
 int STATUS_ECC_MASK ; 
#define  STATUS_ECC_NO_BITFLIPS 129 
#define  STATUS_ECC_UNCOR_ERROR 128 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 
 int stub1 (struct spinand_device*,int) ; 

__attribute__((used)) static int spinand_check_ecc_status(struct spinand_device *spinand, u8 status)
{
	struct nand_device *nand = spinand_to_nand(spinand);

	if (spinand->eccinfo.get_status)
		return spinand->eccinfo.get_status(spinand, status);

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case STATUS_ECC_HAS_BITFLIPS:
		/*
		 * We have no way to know exactly how many bitflips have been
		 * fixed, so let's return the maximum possible value so that
		 * wear-leveling layers move the data immediately.
		 */
		return nand->eccreq.strength;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	default:
		break;
	}

	return -EINVAL;
}