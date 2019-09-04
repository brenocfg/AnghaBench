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
typedef  size_t u32 ;
struct microcode {int /*<<< orphan*/ * code; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  code_size; } ;
struct cpt_device {int /*<<< orphan*/  reg_base; TYPE_1__* pdev; struct microcode* mcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_PF_ENGX_UCODE_BASE (int /*<<< orphan*/ ,size_t) ; 
 size_t CPT_MAX_CORE_GROUPS ; 
 size_t CPT_MAX_TOTAL_CORES ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpt_unload_microcode(struct cpt_device *cpt)
{
	u32 grp = 0, core;

	/* Free microcode bases and reset group masks */
	for (grp = 0; grp < CPT_MAX_CORE_GROUPS; grp++) {
		struct microcode *mcode = &cpt->mcode[grp];

		if (cpt->mcode[grp].code)
			dma_free_coherent(&cpt->pdev->dev, mcode->code_size,
					  mcode->code, mcode->phys_base);
		mcode->code = NULL;
	}
	/* Clear UCODE_BASE registers for all engines */
	for (core = 0; core < CPT_MAX_TOTAL_CORES; core++)
		cpt_write_csr64(cpt->reg_base,
				CPTX_PF_ENGX_UCODE_BASE(0, core), 0ull);
}