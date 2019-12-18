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
#define  GD5FXGQ4UXFXXG_STATUS_ECC_1_3_BITFLIPS 130 
 int GD5FXGQ4UXFXXG_STATUS_ECC_MASK ; 
#define  GD5FXGQ4UXFXXG_STATUS_ECC_NO_BITFLIPS 129 
#define  GD5FXGQ4UXFXXG_STATUS_ECC_UNCOR_ERROR 128 

__attribute__((used)) static int gd5fxgq4ufxxg_ecc_get_status(struct spinand_device *spinand,
					u8 status)
{
	switch (status & GD5FXGQ4UXFXXG_STATUS_ECC_MASK) {
	case GD5FXGQ4UXFXXG_STATUS_ECC_NO_BITFLIPS:
		return 0;

	case GD5FXGQ4UXFXXG_STATUS_ECC_1_3_BITFLIPS:
		return 3;

	case GD5FXGQ4UXFXXG_STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	default: /* (2 << 4) through (6 << 4) are 4-8 corrected errors */
		return ((status & GD5FXGQ4UXFXXG_STATUS_ECC_MASK) >> 4) + 2;
	}

	return -EINVAL;
}