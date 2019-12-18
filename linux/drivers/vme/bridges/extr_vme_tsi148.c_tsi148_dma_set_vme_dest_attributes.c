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
typedef  int u32 ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int TSI148_LCSR_DDAT_2eSSTM_160 ; 
 int TSI148_LCSR_DDAT_2eSSTM_267 ; 
 int TSI148_LCSR_DDAT_2eSSTM_320 ; 
 int TSI148_LCSR_DDAT_AMODE_A16 ; 
 int TSI148_LCSR_DDAT_AMODE_A24 ; 
 int TSI148_LCSR_DDAT_AMODE_A32 ; 
 int TSI148_LCSR_DDAT_AMODE_A64 ; 
 int TSI148_LCSR_DDAT_AMODE_CRCSR ; 
 int TSI148_LCSR_DDAT_AMODE_USER1 ; 
 int TSI148_LCSR_DDAT_AMODE_USER2 ; 
 int TSI148_LCSR_DDAT_AMODE_USER3 ; 
 int TSI148_LCSR_DDAT_AMODE_USER4 ; 
 int TSI148_LCSR_DDAT_DBW_16 ; 
 int TSI148_LCSR_DDAT_DBW_32 ; 
 int TSI148_LCSR_DDAT_PGM ; 
 int TSI148_LCSR_DDAT_SUP ; 
 int TSI148_LCSR_DDAT_TM_2eSST ; 
 int TSI148_LCSR_DDAT_TM_2eSSTB ; 
 int TSI148_LCSR_DDAT_TM_2eVME ; 
 int TSI148_LCSR_DDAT_TM_BLT ; 
 int TSI148_LCSR_DDAT_TM_MBLT ; 
 int TSI148_LCSR_DDAT_TM_SCT ; 
 int VME_2eSST ; 
#define  VME_2eSST160 141 
#define  VME_2eSST267 140 
#define  VME_2eSST320 139 
 int VME_2eSSTB ; 
 int VME_2eVME ; 
#define  VME_A16 138 
#define  VME_A24 137 
#define  VME_A32 136 
#define  VME_A64 135 
 int VME_BLT ; 
#define  VME_CRCSR 134 
#define  VME_D16 133 
#define  VME_D32 132 
 int VME_MBLT ; 
 int VME_PROG ; 
 int VME_SCT ; 
 int VME_SUPER ; 
#define  VME_USER1 131 
#define  VME_USER2 130 
#define  VME_USER3 129 
#define  VME_USER4 128 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int tsi148_dma_set_vme_dest_attributes(struct device *dev, __be32 *attr,
	u32 aspace, u32 cycle, u32 dwidth)
{
	u32 val;

	val = be32_to_cpu(*attr);

	/* Setup 2eSST speeds */
	switch (cycle & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) {
	case VME_2eSST160:
		val |= TSI148_LCSR_DDAT_2eSSTM_160;
		break;
	case VME_2eSST267:
		val |= TSI148_LCSR_DDAT_2eSSTM_267;
		break;
	case VME_2eSST320:
		val |= TSI148_LCSR_DDAT_2eSSTM_320;
		break;
	}

	/* Setup cycle types */
	if (cycle & VME_SCT)
		val |= TSI148_LCSR_DDAT_TM_SCT;

	if (cycle & VME_BLT)
		val |= TSI148_LCSR_DDAT_TM_BLT;

	if (cycle & VME_MBLT)
		val |= TSI148_LCSR_DDAT_TM_MBLT;

	if (cycle & VME_2eVME)
		val |= TSI148_LCSR_DDAT_TM_2eVME;

	if (cycle & VME_2eSST)
		val |= TSI148_LCSR_DDAT_TM_2eSST;

	if (cycle & VME_2eSSTB) {
		dev_err(dev, "Currently not setting Broadcast Select "
			"Registers\n");
		val |= TSI148_LCSR_DDAT_TM_2eSSTB;
	}

	/* Setup data width */
	switch (dwidth) {
	case VME_D16:
		val |= TSI148_LCSR_DDAT_DBW_16;
		break;
	case VME_D32:
		val |= TSI148_LCSR_DDAT_DBW_32;
		break;
	default:
		dev_err(dev, "Invalid data width\n");
		return -EINVAL;
	}

	/* Setup address space */
	switch (aspace) {
	case VME_A16:
		val |= TSI148_LCSR_DDAT_AMODE_A16;
		break;
	case VME_A24:
		val |= TSI148_LCSR_DDAT_AMODE_A24;
		break;
	case VME_A32:
		val |= TSI148_LCSR_DDAT_AMODE_A32;
		break;
	case VME_A64:
		val |= TSI148_LCSR_DDAT_AMODE_A64;
		break;
	case VME_CRCSR:
		val |= TSI148_LCSR_DDAT_AMODE_CRCSR;
		break;
	case VME_USER1:
		val |= TSI148_LCSR_DDAT_AMODE_USER1;
		break;
	case VME_USER2:
		val |= TSI148_LCSR_DDAT_AMODE_USER2;
		break;
	case VME_USER3:
		val |= TSI148_LCSR_DDAT_AMODE_USER3;
		break;
	case VME_USER4:
		val |= TSI148_LCSR_DDAT_AMODE_USER4;
		break;
	default:
		dev_err(dev, "Invalid address space\n");
		return -EINVAL;
		break;
	}

	if (cycle & VME_SUPER)
		val |= TSI148_LCSR_DDAT_SUP;
	if (cycle & VME_PROG)
		val |= TSI148_LCSR_DDAT_PGM;

	*attr = cpu_to_be32(val);

	return 0;
}