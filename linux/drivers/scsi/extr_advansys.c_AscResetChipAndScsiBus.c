#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  iop_base; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_1__ ASC_DVC_VAR ;

/* Variables and functions */
 int AscGetChipStatus (int /*<<< orphan*/ ) ; 
 int AscIsChipHalted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipControl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscSetChipIH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscStopChip (int /*<<< orphan*/ ) ; 
 int CC_CHIP_RESET ; 
 int CC_HALT ; 
 int CC_SCSI_RESET ; 
 int /*<<< orphan*/  CIW_CLR_SCSI_RESET_INT ; 
 int CSW_SCSI_RESET_ACTIVE ; 
 int /*<<< orphan*/  INS_HALT ; 
 int /*<<< orphan*/  INS_RFLAG_WTM ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool AscResetChipAndScsiBus(ASC_DVC_VAR *asc_dvc)
{
	PortAddr iop_base;
	int i = 10;

	iop_base = asc_dvc->iop_base;
	while ((AscGetChipStatus(iop_base) & CSW_SCSI_RESET_ACTIVE)
	       && (i-- > 0)) {
		mdelay(100);
	}
	AscStopChip(iop_base);
	AscSetChipControl(iop_base, CC_CHIP_RESET | CC_SCSI_RESET | CC_HALT);
	udelay(60);
	AscSetChipIH(iop_base, INS_RFLAG_WTM);
	AscSetChipIH(iop_base, INS_HALT);
	AscSetChipControl(iop_base, CC_CHIP_RESET | CC_HALT);
	AscSetChipControl(iop_base, CC_HALT);
	mdelay(200);
	AscSetChipStatus(iop_base, CIW_CLR_SCSI_RESET_INT);
	AscSetChipStatus(iop_base, 0);
	return (AscIsChipHalted(iop_base));
}