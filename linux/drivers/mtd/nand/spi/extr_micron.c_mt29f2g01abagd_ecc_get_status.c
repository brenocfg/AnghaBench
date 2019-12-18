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
#define  MICRON_STATUS_ECC_1TO3_BITFLIPS 132 
#define  MICRON_STATUS_ECC_4TO6_BITFLIPS 131 
#define  MICRON_STATUS_ECC_7TO8_BITFLIPS 130 
 int MICRON_STATUS_ECC_MASK ; 
#define  STATUS_ECC_NO_BITFLIPS 129 
#define  STATUS_ECC_UNCOR_ERROR 128 

__attribute__((used)) static int mt29f2g01abagd_ecc_get_status(struct spinand_device *spinand,
					 u8 status)
{
	switch (status & MICRON_STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	case MICRON_STATUS_ECC_1TO3_BITFLIPS:
		return 3;

	case MICRON_STATUS_ECC_4TO6_BITFLIPS:
		return 6;

	case MICRON_STATUS_ECC_7TO8_BITFLIPS:
		return 8;

	default:
		break;
	}

	return -EINVAL;
}