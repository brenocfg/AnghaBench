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
typedef  int /*<<< orphan*/  uint32_t ;
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_VM_XGMI_LFB_CNTL ; 
 int /*<<< orphan*/  PF_MAX_REGION ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool dce121_xgmi_enabled(struct dce_hwseq *hws)
{
	uint32_t pf_max_region;

	REG_GET(MC_VM_XGMI_LFB_CNTL, PF_MAX_REGION, &pf_max_region);
	/* PF_MAX_REGION == 0 means xgmi is disabled */
	return !!pf_max_region;
}