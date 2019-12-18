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
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CM_DTRAN_CTRL ; 
 int /*<<< orphan*/  DTRAN_CTRL_DM_START ; 
 int /*<<< orphan*/  TMIO_STAT_DATAEND ; 
 int /*<<< orphan*/  renesas_sdhi_internal_dmac_dm_write (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_mmc_enable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void renesas_sdhi_internal_dmac_issue_tasklet_fn(unsigned long arg)
{
	struct tmio_mmc_host *host = (struct tmio_mmc_host *)arg;

	tmio_mmc_enable_mmc_irqs(host, TMIO_STAT_DATAEND);

	/* start the DMAC */
	renesas_sdhi_internal_dmac_dm_write(host, DM_CM_DTRAN_CTRL,
					    DTRAN_CTRL_DM_START);
}