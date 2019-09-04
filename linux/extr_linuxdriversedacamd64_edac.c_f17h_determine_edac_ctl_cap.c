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
typedef  size_t u8 ;
struct mem_ctl_info {int /*<<< orphan*/  edac_ctl_cap; } ;
struct amd64_pvt {TYPE_1__* umc; } ;
struct TYPE_2__ {int sdp_ctrl; int umc_cap_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_FLAG_S4ECD4ED ; 
 int /*<<< orphan*/  EDAC_FLAG_SECDED ; 
 size_t NUM_UMCS ; 
 int UMC_ECC_CHIPKILL_CAP ; 
 int UMC_ECC_ENABLED ; 
 int UMC_SDP_INIT ; 

__attribute__((used)) static inline void
f17h_determine_edac_ctl_cap(struct mem_ctl_info *mci, struct amd64_pvt *pvt)
{
	u8 i, ecc_en = 1, cpk_en = 1;

	for (i = 0; i < NUM_UMCS; i++) {
		if (pvt->umc[i].sdp_ctrl & UMC_SDP_INIT) {
			ecc_en &= !!(pvt->umc[i].umc_cap_hi & UMC_ECC_ENABLED);
			cpk_en &= !!(pvt->umc[i].umc_cap_hi & UMC_ECC_CHIPKILL_CAP);
		}
	}

	/* Set chipkill only if ECC is enabled: */
	if (ecc_en) {
		mci->edac_ctl_cap |= EDAC_FLAG_SECDED;

		if (cpk_en)
			mci->edac_ctl_cap |= EDAC_FLAG_S4ECD4ED;
	}
}