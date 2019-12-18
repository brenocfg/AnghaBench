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
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {int flags; scalar_t__ version; } ;
struct mmc_command {scalar_t__ opcode; TYPE_1__* mrq; } ;
struct TYPE_2__ {scalar_t__ sbc; } ;

/* Variables and functions */
 int SDHCI_AUTO_CMD23 ; 
 int /*<<< orphan*/  SDHCI_CMD23_ENABLE ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 scalar_t__ SDHCI_SPEC_410 ; 
 int /*<<< orphan*/  SDHCI_TRNS_AUTO_CMD12 ; 
 int /*<<< orphan*/  SDHCI_TRNS_AUTO_CMD23 ; 
 int /*<<< orphan*/  SDHCI_TRNS_AUTO_SEL ; 
 scalar_t__ SD_IO_RW_EXTENDED ; 
 scalar_t__ sdhci_auto_cmd12 (struct sdhci_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sdhci_auto_cmd_select(struct sdhci_host *host,
					 struct mmc_command *cmd,
					 u16 *mode)
{
	bool use_cmd12 = sdhci_auto_cmd12(host, cmd->mrq) &&
			 (cmd->opcode != SD_IO_RW_EXTENDED);
	bool use_cmd23 = cmd->mrq->sbc && (host->flags & SDHCI_AUTO_CMD23);
	u16 ctrl2;

	/*
	 * In case of Version 4.10 or later, use of 'Auto CMD Auto
	 * Select' is recommended rather than use of 'Auto CMD12
	 * Enable' or 'Auto CMD23 Enable'.
	 */
	if (host->version >= SDHCI_SPEC_410 && (use_cmd12 || use_cmd23)) {
		*mode |= SDHCI_TRNS_AUTO_SEL;

		ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
		if (use_cmd23)
			ctrl2 |= SDHCI_CMD23_ENABLE;
		else
			ctrl2 &= ~SDHCI_CMD23_ENABLE;
		sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);

		return;
	}

	/*
	 * If we are sending CMD23, CMD12 never gets sent
	 * on successful completion (so no Auto-CMD12).
	 */
	if (use_cmd12)
		*mode |= SDHCI_TRNS_AUTO_CMD12;
	else if (use_cmd23)
		*mode |= SDHCI_TRNS_AUTO_CMD23;
}