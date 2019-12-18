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
struct spinand_device {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
#define  GD5FXGQ4XA_STATUS_ECC_1_7_BITFLIPS 131 
#define  GD5FXGQ4XA_STATUS_ECC_8_BITFLIPS 130 
 int STATUS_ECC_MASK ; 
#define  STATUS_ECC_NO_BITFLIPS 129 
#define  STATUS_ECC_UNCOR_ERROR 128 

__attribute__((used)) static int gd5fxgq4xa_ecc_get_status(struct spinand_device *spinand,
					 u8 status)
{
	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case GD5FXGQ4XA_STATUS_ECC_1_7_BITFLIPS:
		/* 1-7 bits are flipped. return the maximum. */
		return 7;

	case GD5FXGQ4XA_STATUS_ECC_8_BITFLIPS:
		return 8;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	default:
		break;
	}

	return -EINVAL;
}