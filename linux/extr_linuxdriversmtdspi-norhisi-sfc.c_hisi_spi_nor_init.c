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
struct hifmc_host {scalar_t__ regbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_DESELECT_TIME ; 
 int /*<<< orphan*/  CS_HOLD_TIME ; 
 int /*<<< orphan*/  CS_SETUP_TIME ; 
 scalar_t__ FMC_SPI_TIMING_CFG ; 
 int TIMING_CFG_TCSH (int /*<<< orphan*/ ) ; 
 int TIMING_CFG_TCSS (int /*<<< orphan*/ ) ; 
 int TIMING_CFG_TSHSL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hisi_spi_nor_init(struct hifmc_host *host)
{
	u32 reg;

	reg = TIMING_CFG_TCSH(CS_HOLD_TIME)
		| TIMING_CFG_TCSS(CS_SETUP_TIME)
		| TIMING_CFG_TSHSL(CS_DESELECT_TIME);
	writel(reg, host->regbase + FMC_SPI_TIMING_CFG);
}