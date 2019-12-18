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

/* Variables and functions */
#define  QTN_CHIP_ID_PEARL 131 
#define  QTN_CHIP_ID_PEARL_B 130 
#define  QTN_CHIP_ID_PEARL_C 129 
#define  QTN_CHIP_ID_TOPAZ 128 

const char *qtnf_chipid_to_string(unsigned long chip_id)
{
	switch (chip_id) {
	case QTN_CHIP_ID_TOPAZ:
		return "Topaz";
	case QTN_CHIP_ID_PEARL:
		return "Pearl revA";
	case QTN_CHIP_ID_PEARL_B:
		return "Pearl revB";
	case QTN_CHIP_ID_PEARL_C:
		return "Pearl revC";
	default:
		return "unknown";
	}
}