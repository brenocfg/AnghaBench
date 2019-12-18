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
typedef  scalar_t__ u32 ;
struct vme_master_resource {unsigned int number; TYPE_1__* parent; } ;
struct tsi148_driver {scalar_t__ base; } ;
struct TYPE_2__ {struct tsi148_driver* driver_priv; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_OFFSET_OTAT ; 
 scalar_t__ TSI148_LCSR_OFFSET_OTEAL ; 
 scalar_t__ TSI148_LCSR_OFFSET_OTEAU ; 
 scalar_t__ TSI148_LCSR_OFFSET_OTOFL ; 
 scalar_t__ TSI148_LCSR_OFFSET_OTOFU ; 
 scalar_t__ TSI148_LCSR_OFFSET_OTSAL ; 
 scalar_t__ TSI148_LCSR_OFFSET_OTSAU ; 
 scalar_t__* TSI148_LCSR_OT ; 
 unsigned int TSI148_LCSR_OTAT_2eSSTM_160 ; 
 unsigned int TSI148_LCSR_OTAT_2eSSTM_267 ; 
 unsigned int TSI148_LCSR_OTAT_2eSSTM_320 ; 
 unsigned int TSI148_LCSR_OTAT_2eSSTM_M ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_A16 ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_A24 ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_A32 ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_A64 ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_CRCSR ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_M ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_USER1 ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_USER2 ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_USER3 ; 
 unsigned int TSI148_LCSR_OTAT_AMODE_USER4 ; 
 unsigned int TSI148_LCSR_OTAT_DBW_16 ; 
 unsigned int TSI148_LCSR_OTAT_DBW_32 ; 
 unsigned int TSI148_LCSR_OTAT_DBW_M ; 
 unsigned int TSI148_LCSR_OTAT_EN ; 
 unsigned int TSI148_LCSR_OTAT_PGM ; 
 unsigned int TSI148_LCSR_OTAT_SUP ; 
 unsigned int TSI148_LCSR_OTAT_TM_2eSST ; 
 unsigned int TSI148_LCSR_OTAT_TM_2eSSTB ; 
 unsigned int TSI148_LCSR_OTAT_TM_2eVME ; 
 unsigned int TSI148_LCSR_OTAT_TM_BLT ; 
 unsigned int TSI148_LCSR_OTAT_TM_M ; 
 unsigned int TSI148_LCSR_OTAT_TM_MBLT ; 
 unsigned int TSI148_LCSR_OTAT_TM_SCT ; 
 scalar_t__ VME_2eSST ; 
 scalar_t__ VME_2eSST160 ; 
 scalar_t__ VME_2eSST267 ; 
 scalar_t__ VME_2eSST320 ; 
 scalar_t__ VME_2eSSTB ; 
 scalar_t__ VME_2eVME ; 
 scalar_t__ VME_A16 ; 
 scalar_t__ VME_A24 ; 
 scalar_t__ VME_A32 ; 
 scalar_t__ VME_A64 ; 
 scalar_t__ VME_BLT ; 
 scalar_t__ VME_CRCSR ; 
 scalar_t__ VME_D16 ; 
 scalar_t__ VME_D32 ; 
 scalar_t__ VME_DATA ; 
 scalar_t__ VME_MBLT ; 
 scalar_t__ VME_PROG ; 
 scalar_t__ VME_SCT ; 
 scalar_t__ VME_SUPER ; 
 scalar_t__ VME_USER ; 
 scalar_t__ VME_USER1 ; 
 scalar_t__ VME_USER2 ; 
 scalar_t__ VME_USER3 ; 
 scalar_t__ VME_USER4 ; 
 unsigned int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  reg_join (unsigned int,unsigned int,unsigned long long*) ; 

__attribute__((used)) static int __tsi148_master_get(struct vme_master_resource *image, int *enabled,
	unsigned long long *vme_base, unsigned long long *size, u32 *aspace,
	u32 *cycle, u32 *dwidth)
{
	unsigned int i, ctl;
	unsigned int pci_base_low, pci_base_high;
	unsigned int pci_bound_low, pci_bound_high;
	unsigned int vme_offset_low, vme_offset_high;

	unsigned long long pci_base, pci_bound, vme_offset;
	struct tsi148_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	ctl = ioread32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTAT);

	pci_base_high = ioread32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAU);
	pci_base_low = ioread32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAL);
	pci_bound_high = ioread32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTEAU);
	pci_bound_low = ioread32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTEAL);
	vme_offset_high = ioread32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTOFU);
	vme_offset_low = ioread32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTOFL);

	/* Convert 64-bit variables to 2x 32-bit variables */
	reg_join(pci_base_high, pci_base_low, &pci_base);
	reg_join(pci_bound_high, pci_bound_low, &pci_bound);
	reg_join(vme_offset_high, vme_offset_low, &vme_offset);

	*vme_base = pci_base + vme_offset;
	*size = (unsigned long long)(pci_bound - pci_base) + 0x10000;

	*enabled = 0;
	*aspace = 0;
	*cycle = 0;
	*dwidth = 0;

	if (ctl & TSI148_LCSR_OTAT_EN)
		*enabled = 1;

	/* Setup address space */
	if ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_A16)
		*aspace |= VME_A16;
	if ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_A24)
		*aspace |= VME_A24;
	if ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_A32)
		*aspace |= VME_A32;
	if ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_A64)
		*aspace |= VME_A64;
	if ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_CRCSR)
		*aspace |= VME_CRCSR;
	if ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_USER1)
		*aspace |= VME_USER1;
	if ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_USER2)
		*aspace |= VME_USER2;
	if ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_USER3)
		*aspace |= VME_USER3;
	if ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_USER4)
		*aspace |= VME_USER4;

	/* Setup 2eSST speeds */
	if ((ctl & TSI148_LCSR_OTAT_2eSSTM_M) == TSI148_LCSR_OTAT_2eSSTM_160)
		*cycle |= VME_2eSST160;
	if ((ctl & TSI148_LCSR_OTAT_2eSSTM_M) == TSI148_LCSR_OTAT_2eSSTM_267)
		*cycle |= VME_2eSST267;
	if ((ctl & TSI148_LCSR_OTAT_2eSSTM_M) == TSI148_LCSR_OTAT_2eSSTM_320)
		*cycle |= VME_2eSST320;

	/* Setup cycle types */
	if ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_SCT)
		*cycle |= VME_SCT;
	if ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_BLT)
		*cycle |= VME_BLT;
	if ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_MBLT)
		*cycle |= VME_MBLT;
	if ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_2eVME)
		*cycle |= VME_2eVME;
	if ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_2eSST)
		*cycle |= VME_2eSST;
	if ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_2eSSTB)
		*cycle |= VME_2eSSTB;

	if (ctl & TSI148_LCSR_OTAT_SUP)
		*cycle |= VME_SUPER;
	else
		*cycle |= VME_USER;

	if (ctl & TSI148_LCSR_OTAT_PGM)
		*cycle |= VME_PROG;
	else
		*cycle |= VME_DATA;

	/* Setup data width */
	if ((ctl & TSI148_LCSR_OTAT_DBW_M) == TSI148_LCSR_OTAT_DBW_16)
		*dwidth = VME_D16;
	if ((ctl & TSI148_LCSR_OTAT_DBW_M) == TSI148_LCSR_OTAT_DBW_32)
		*dwidth = VME_D32;

	return 0;
}