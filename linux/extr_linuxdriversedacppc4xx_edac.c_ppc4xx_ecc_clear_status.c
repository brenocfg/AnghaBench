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
struct ppc4xx_edac_pdata {int /*<<< orphan*/  dcr_host; } ;
struct ppc4xx_ecc_status {int ecces; int wmirq; int besr; } ;
struct mem_ctl_info {struct ppc4xx_edac_pdata* pvt_info; } ;
typedef  int /*<<< orphan*/  dcr_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDRAM_BEARH ; 
 int /*<<< orphan*/  SDRAM_BEARL ; 
 int /*<<< orphan*/  SDRAM_BESR ; 
 int SDRAM_BESR_MASK ; 
 int /*<<< orphan*/  SDRAM_ECCES ; 
 int SDRAM_ECCES_MASK ; 
 int /*<<< orphan*/  SDRAM_WMIRQ ; 
 int SDRAM_WMIRQ_MASK ; 
 int /*<<< orphan*/  mtsdram (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ppc4xx_ecc_clear_status(const struct mem_ctl_info *mci,
			const struct ppc4xx_ecc_status *status)
{
	const struct ppc4xx_edac_pdata *pdata = mci->pvt_info;
	const dcr_host_t *dcr_host = &pdata->dcr_host;

	mtsdram(dcr_host, SDRAM_ECCES,	status->ecces & SDRAM_ECCES_MASK);
	mtsdram(dcr_host, SDRAM_WMIRQ,	status->wmirq & SDRAM_WMIRQ_MASK);
	mtsdram(dcr_host, SDRAM_BESR,	status->besr & SDRAM_BESR_MASK);
	mtsdram(dcr_host, SDRAM_BEARL,	0);
	mtsdram(dcr_host, SDRAM_BEARH,	0);
}