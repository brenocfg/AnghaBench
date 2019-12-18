#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  aapl_bus_id; int /*<<< orphan*/  node; scalar_t__ kauai_fcr; int /*<<< orphan*/  irq; scalar_t__* timings; } ;
typedef  TYPE_1__ pmac_ide_hwif_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* feature_call ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int KAUAI_FCR_UATA_ENABLE ; 
 int KAUAI_FCR_UATA_RESET_N ; 
 int /*<<< orphan*/  PMAC_FTR_IDE_ENABLE ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ on_media_bay (TYPE_1__*) ; 
 TYPE_2__ ppc_md ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pmac_ide_do_suspend(pmac_ide_hwif_t *pmif)
{
	/* We clear the timings */
	pmif->timings[0] = 0;
	pmif->timings[1] = 0;
	
	disable_irq(pmif->irq);

	/* The media bay will handle itself just fine */
	if (on_media_bay(pmif))
		return 0;
	
	/* Kauai has bus control FCRs directly here */
	if (pmif->kauai_fcr) {
		u32 fcr = readl(pmif->kauai_fcr);
		fcr &= ~(KAUAI_FCR_UATA_RESET_N | KAUAI_FCR_UATA_ENABLE);
		writel(fcr, pmif->kauai_fcr);
	}

	/* Disable the bus on older machines and the cell on kauai */
	ppc_md.feature_call(PMAC_FTR_IDE_ENABLE, pmif->node, pmif->aapl_bus_id,
			    0);

	return 0;
}