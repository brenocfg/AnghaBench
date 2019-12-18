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
struct intel_guc {int /*<<< orphan*/  ads_vma; } ;

/* Variables and functions */
 int GUC_ADS_ADDR_SHIFT ; 
 int PAGE_SHIFT ; 
 int intel_guc_ggtt_offset (struct intel_guc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 guc_ctl_ads_flags(struct intel_guc *guc)
{
	u32 ads = intel_guc_ggtt_offset(guc, guc->ads_vma) >> PAGE_SHIFT;
	u32 flags = ads << GUC_ADS_ADDR_SHIFT;

	return flags;
}