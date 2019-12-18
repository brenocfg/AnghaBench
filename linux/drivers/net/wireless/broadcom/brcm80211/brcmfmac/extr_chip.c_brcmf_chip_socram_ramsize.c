#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int u32 ;
struct TYPE_7__ {int rev; } ;
struct brcmf_core_priv {TYPE_2__* chip; TYPE_3__ pub; } ;
struct TYPE_5__ {int chip; int chiprev; } ;
struct TYPE_6__ {TYPE_1__ pub; } ;

/* Variables and functions */
#define  BRCM_CC_4334_CHIP_ID 129 
#define  BRCM_CC_43430_CHIP_ID 128 
 int /*<<< orphan*/  SOCRAMREGOFFS (int) ; 
 int SRCI_LSS_MASK ; 
 int SRCI_LSS_SHIFT ; 
 int SRCI_SRBSZ_MASK ; 
 int SRCI_SRNB_MASK ; 
 int SRCI_SRNB_MASK_EXT ; 
 int SRCI_SRNB_SHIFT ; 
 int SR_BSZ_BASE ; 
 scalar_t__ WARN_ON (int) ; 
 int brcmf_chip_core_read32 (struct brcmf_core_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_chip_iscoreup (TYPE_3__*) ; 
 int /*<<< orphan*/  brcmf_chip_resetcore (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmf_chip_socram_banksize (struct brcmf_core_priv*,int,int*) ; 

__attribute__((used)) static void brcmf_chip_socram_ramsize(struct brcmf_core_priv *sr, u32 *ramsize,
				      u32 *srsize)
{
	u32 coreinfo;
	uint nb, banksize, lss;
	bool retent;
	int i;

	*ramsize = 0;
	*srsize = 0;

	if (WARN_ON(sr->pub.rev < 4))
		return;

	if (!brcmf_chip_iscoreup(&sr->pub))
		brcmf_chip_resetcore(&sr->pub, 0, 0, 0);

	/* Get info for determining size */
	coreinfo = brcmf_chip_core_read32(sr, SOCRAMREGOFFS(coreinfo));
	nb = (coreinfo & SRCI_SRNB_MASK) >> SRCI_SRNB_SHIFT;

	if ((sr->pub.rev <= 7) || (sr->pub.rev == 12)) {
		banksize = (coreinfo & SRCI_SRBSZ_MASK);
		lss = (coreinfo & SRCI_LSS_MASK) >> SRCI_LSS_SHIFT;
		if (lss != 0)
			nb--;
		*ramsize = nb * (1 << (banksize + SR_BSZ_BASE));
		if (lss != 0)
			*ramsize += (1 << ((lss - 1) + SR_BSZ_BASE));
	} else {
		/* length of SRAM Banks increased for corerev greater than 23 */
		if (sr->pub.rev >= 23) {
			nb = (coreinfo & (SRCI_SRNB_MASK | SRCI_SRNB_MASK_EXT))
				>> SRCI_SRNB_SHIFT;
		} else {
			nb = (coreinfo & SRCI_SRNB_MASK) >> SRCI_SRNB_SHIFT;
		}
		for (i = 0; i < nb; i++) {
			retent = brcmf_chip_socram_banksize(sr, i, &banksize);
			*ramsize += banksize;
			if (retent)
				*srsize += banksize;
		}
	}

	/* hardcoded save&restore memory sizes */
	switch (sr->chip->pub.chip) {
	case BRCM_CC_4334_CHIP_ID:
		if (sr->chip->pub.chiprev < 2)
			*srsize = (32 * 1024);
		break;
	case BRCM_CC_43430_CHIP_ID:
		/* assume sr for now as we can not check
		 * firmware sr capability at this point.
		 */
		*srsize = (64 * 1024);
		break;
	default:
		break;
	}
}