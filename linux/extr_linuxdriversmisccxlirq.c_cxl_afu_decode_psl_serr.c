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
typedef  int u64 ;
struct cxl_afu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CXL_PSL_SERR_An_AE ; 
 int CXL_PSL_SERR_An_afudis ; 
 int CXL_PSL_SERR_An_afudup ; 
 int CXL_PSL_SERR_An_afuov ; 
 int CXL_PSL_SERR_An_afupar ; 
 int CXL_PSL_SERR_An_afuto ; 
 int CXL_PSL_SERR_An_badctx ; 
 int CXL_PSL_SERR_An_badsrc ; 
 int CXL_PSL_SERR_An_llcmdis ; 
 int CXL_PSL_SERR_An_llcmdto ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,...) ; 

void cxl_afu_decode_psl_serr(struct cxl_afu *afu, u64 serr)
{
	dev_crit(&afu->dev,
		 "PSL Slice error received. Check AFU for root cause.\n");
	dev_crit(&afu->dev, "PSL_SERR_An: 0x%016llx\n", serr);
	if (serr & CXL_PSL_SERR_An_afuto)
		dev_crit(&afu->dev, "AFU MMIO Timeout\n");
	if (serr & CXL_PSL_SERR_An_afudis)
		dev_crit(&afu->dev,
			 "MMIO targeted Accelerator that was not enabled\n");
	if (serr & CXL_PSL_SERR_An_afuov)
		dev_crit(&afu->dev, "AFU CTAG Overflow\n");
	if (serr & CXL_PSL_SERR_An_badsrc)
		dev_crit(&afu->dev, "Bad Interrupt Source\n");
	if (serr & CXL_PSL_SERR_An_badctx)
		dev_crit(&afu->dev, "Bad Context Handle\n");
	if (serr & CXL_PSL_SERR_An_llcmdis)
		dev_crit(&afu->dev, "LLCMD to Disabled AFU\n");
	if (serr & CXL_PSL_SERR_An_llcmdto)
		dev_crit(&afu->dev, "LLCMD Timeout to AFU\n");
	if (serr & CXL_PSL_SERR_An_afupar)
		dev_crit(&afu->dev, "AFU MMIO Parity Error\n");
	if (serr & CXL_PSL_SERR_An_afudup)
		dev_crit(&afu->dev, "AFU MMIO Duplicate CTAG Error\n");
	if (serr & CXL_PSL_SERR_An_AE)
		dev_crit(&afu->dev,
			 "AFU asserted JDONE with JERROR in AFU Directed Mode\n");
}