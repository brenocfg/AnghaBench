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
struct brcmf_core {int rev; } ;
struct brcmf_chip {int cc_caps_ext; } ;

/* Variables and functions */
 int BCMA_CC_CAP_EXT_AOB_PRESENT ; 
 int /*<<< orphan*/  BCMA_CORE_PMU ; 
 struct brcmf_core* brcmf_chip_get_chipcommon (struct brcmf_chip*) ; 
 struct brcmf_core* brcmf_chip_get_core (struct brcmf_chip*,int /*<<< orphan*/ ) ; 

struct brcmf_core *brcmf_chip_get_pmu(struct brcmf_chip *pub)
{
	struct brcmf_core *cc = brcmf_chip_get_chipcommon(pub);
	struct brcmf_core *pmu;

	/* See if there is separated PMU core available */
	if (cc->rev >= 35 &&
	    pub->cc_caps_ext & BCMA_CC_CAP_EXT_AOB_PRESENT) {
		pmu = brcmf_chip_get_core(pub, BCMA_CORE_PMU);
		if (pmu)
			return pmu;
	}

	/* Fallback to ChipCommon core for older hardware */
	return cc;
}