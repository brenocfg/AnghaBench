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
#define  PN26G0XA_STATUS_ECC_1_7_CORRECTED 131 
#define  PN26G0XA_STATUS_ECC_8_CORRECTED 130 
 int PN26G0XA_STATUS_ECC_BITMASK ; 
#define  PN26G0XA_STATUS_ECC_ERRORED 129 
#define  PN26G0XA_STATUS_ECC_NONE_DETECTED 128 

__attribute__((used)) static int pn26g0xa_ecc_get_status(struct spinand_device *spinand,
				   u8 status)
{
	switch (status & PN26G0XA_STATUS_ECC_BITMASK) {
	case PN26G0XA_STATUS_ECC_NONE_DETECTED:
		return 0;

	case PN26G0XA_STATUS_ECC_1_7_CORRECTED:
		return 7;	/* Return upper limit by convention */

	case PN26G0XA_STATUS_ECC_8_CORRECTED:
		return 8;

	case PN26G0XA_STATUS_ECC_ERRORED:
		return -EBADMSG;

	default:
		break;
	}

	return -EINVAL;
}