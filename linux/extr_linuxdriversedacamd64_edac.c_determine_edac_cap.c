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
struct amd64_pvt {int fam; scalar_t__ ext_model; int dclr0; TYPE_1__* umc; } ;
struct TYPE_2__ {int sdp_ctrl; int umc_cfg; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 unsigned long EDAC_FLAG_NONE ; 
 unsigned long EDAC_FLAG_SECDED ; 
 scalar_t__ K8_REV_F ; 
 size_t NUM_UMCS ; 
 int UMC_SDP_INIT ; 

__attribute__((used)) static unsigned long determine_edac_cap(struct amd64_pvt *pvt)
{
	unsigned long edac_cap = EDAC_FLAG_NONE;
	u8 bit;

	if (pvt->umc) {
		u8 i, umc_en_mask = 0, dimm_ecc_en_mask = 0;

		for (i = 0; i < NUM_UMCS; i++) {
			if (!(pvt->umc[i].sdp_ctrl & UMC_SDP_INIT))
				continue;

			umc_en_mask |= BIT(i);

			/* UMC Configuration bit 12 (DimmEccEn) */
			if (pvt->umc[i].umc_cfg & BIT(12))
				dimm_ecc_en_mask |= BIT(i);
		}

		if (umc_en_mask == dimm_ecc_en_mask)
			edac_cap = EDAC_FLAG_SECDED;
	} else {
		bit = (pvt->fam > 0xf || pvt->ext_model >= K8_REV_F)
			? 19
			: 17;

		if (pvt->dclr0 & BIT(bit))
			edac_cap = EDAC_FLAG_SECDED;
	}

	return edac_cap;
}