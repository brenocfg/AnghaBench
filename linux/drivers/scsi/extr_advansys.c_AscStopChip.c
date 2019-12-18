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
typedef  int uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int AscGetChipControl (int /*<<< orphan*/ ) ; 
 int AscGetChipStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipControl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscSetChipIH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CC_DIAG ; 
 int CC_HALT ; 
 int CC_SINGLE_STEP ; 
 int CC_TEST ; 
 int CSW_HALTED ; 
 int /*<<< orphan*/  INS_HALT ; 
 int /*<<< orphan*/  INS_RFLAG_WTM ; 

__attribute__((used)) static bool AscStopChip(PortAddr iop_base)
{
	uchar cc_val;

	cc_val =
	    AscGetChipControl(iop_base) &
	    (~(CC_SINGLE_STEP | CC_TEST | CC_DIAG));
	AscSetChipControl(iop_base, (uchar)(cc_val | CC_HALT));
	AscSetChipIH(iop_base, INS_HALT);
	AscSetChipIH(iop_base, INS_RFLAG_WTM);
	if ((AscGetChipStatus(iop_base) & CSW_HALTED) == 0) {
		return false;
	}
	return true;
}