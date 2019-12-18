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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 unsigned int SDHCI_CTRL_EXEC_TUNING ; 
 unsigned int SDHCI_CTRL_PRESET_VAL_ENABLE ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 unsigned int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd_tuning_reset(struct sdhci_host *host)
{
	unsigned int val;

	val = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	val |= SDHCI_CTRL_PRESET_VAL_ENABLE | SDHCI_CTRL_EXEC_TUNING;
	sdhci_writew(host, val, SDHCI_HOST_CONTROL2);

	val = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	val &= ~SDHCI_CTRL_EXEC_TUNING;
	sdhci_writew(host, val, SDHCI_HOST_CONTROL2);
}