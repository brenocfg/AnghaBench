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
typedef  scalar_t__ u32 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ FIELD_GET (scalar_t__,scalar_t__) ; 
 scalar_t__ FIELD_PREP (scalar_t__,scalar_t__) ; 
 scalar_t__ GLI_9750_WT_EN_OFF ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_WT ; 
 scalar_t__ SDHCI_GLI_9750_WT_EN ; 
 scalar_t__ sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gl9750_wt_off(struct sdhci_host *host)
{
	u32 wt_value;
	u32 wt_enable;

	wt_value = sdhci_readl(host, SDHCI_GLI_9750_WT);
	wt_enable = FIELD_GET(SDHCI_GLI_9750_WT_EN, wt_value);

	if (wt_enable == GLI_9750_WT_EN_OFF)
		return;

	wt_value &= ~SDHCI_GLI_9750_WT_EN;
	wt_value |= FIELD_PREP(SDHCI_GLI_9750_WT_EN, GLI_9750_WT_EN_OFF);

	sdhci_writel(host, wt_value, SDHCI_GLI_9750_WT);
}