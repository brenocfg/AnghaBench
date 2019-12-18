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
struct debug_drvdata {int edpcsr_present; int edcidsr_present; int edvidsr_present; int pc_has_offset; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_64BIT ; 
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ EDDEVID ; 
 scalar_t__ EDDEVID1 ; 
 int EDDEVID1_PCSR_NO_OFFSET_DIS_AARCH32 ; 
 int EDDEVID1_PCSR_OFFSET_INS_SET ; 
 int EDDEVID1_PCSR_OFFSET_MASK ; 
#define  EDDEVID_IMPL_EDPCSR 130 
#define  EDDEVID_IMPL_EDPCSR_EDCIDSR 129 
#define  EDDEVID_IMPL_FULL 128 
 int EDDEVID_PCSAMPLE_MODE ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void debug_init_arch_data(void *info)
{
	struct debug_drvdata *drvdata = info;
	u32 mode, pcsr_offset;
	u32 eddevid, eddevid1;

	CS_UNLOCK(drvdata->base);

	/* Read device info */
	eddevid  = readl_relaxed(drvdata->base + EDDEVID);
	eddevid1 = readl_relaxed(drvdata->base + EDDEVID1);

	CS_LOCK(drvdata->base);

	/* Parse implementation feature */
	mode = eddevid & EDDEVID_PCSAMPLE_MODE;
	pcsr_offset = eddevid1 & EDDEVID1_PCSR_OFFSET_MASK;

	drvdata->edpcsr_present  = false;
	drvdata->edcidsr_present = false;
	drvdata->edvidsr_present = false;
	drvdata->pc_has_offset   = false;

	switch (mode) {
	case EDDEVID_IMPL_FULL:
		drvdata->edvidsr_present = true;
		/* Fall through */
	case EDDEVID_IMPL_EDPCSR_EDCIDSR:
		drvdata->edcidsr_present = true;
		/* Fall through */
	case EDDEVID_IMPL_EDPCSR:
		/*
		 * In ARM DDI 0487A.k, the EDDEVID1.PCSROffset is used to
		 * define if has the offset for PC sampling value; if read
		 * back EDDEVID1.PCSROffset == 0x2, then this means the debug
		 * module does not sample the instruction set state when
		 * armv8 CPU in AArch32 state.
		 */
		drvdata->edpcsr_present =
			((IS_ENABLED(CONFIG_64BIT) && pcsr_offset != 0) ||
			 (pcsr_offset != EDDEVID1_PCSR_NO_OFFSET_DIS_AARCH32));

		drvdata->pc_has_offset =
			(pcsr_offset == EDDEVID1_PCSR_OFFSET_INS_SET);
		break;
	default:
		break;
	}
}