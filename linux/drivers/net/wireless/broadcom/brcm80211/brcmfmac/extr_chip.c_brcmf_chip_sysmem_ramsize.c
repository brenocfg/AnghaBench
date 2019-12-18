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
struct brcmf_core_priv {int /*<<< orphan*/  pub; } ;

/* Variables and functions */
 int SRCI_SRNB_MASK ; 
 int SRCI_SRNB_SHIFT ; 
 int /*<<< orphan*/  SYSMEMREGOFFS (int) ; 
 int brcmf_chip_core_read32 (struct brcmf_core_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_chip_iscoreup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_chip_resetcore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_chip_socram_banksize (struct brcmf_core_priv*,int,int*) ; 

__attribute__((used)) static u32 brcmf_chip_sysmem_ramsize(struct brcmf_core_priv *sysmem)
{
	u32 memsize = 0;
	u32 coreinfo;
	u32 idx;
	u32 nb;
	u32 banksize;

	if (!brcmf_chip_iscoreup(&sysmem->pub))
		brcmf_chip_resetcore(&sysmem->pub, 0, 0, 0);

	coreinfo = brcmf_chip_core_read32(sysmem, SYSMEMREGOFFS(coreinfo));
	nb = (coreinfo & SRCI_SRNB_MASK) >> SRCI_SRNB_SHIFT;

	for (idx = 0; idx < nb; idx++) {
		brcmf_chip_socram_banksize(sysmem, idx, &banksize);
		memsize += banksize;
	}

	return memsize;
}