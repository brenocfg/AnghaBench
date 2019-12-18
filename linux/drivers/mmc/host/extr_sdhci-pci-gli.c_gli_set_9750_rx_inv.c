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
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLI_9750_MISC_RX_INV_OFF ; 
 int /*<<< orphan*/  GLI_9750_MISC_RX_INV_ON ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_MISC ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_MISC_RX_INV ; 
 int /*<<< orphan*/  gl9750_wt_off (struct sdhci_host*) ; 
 int /*<<< orphan*/  gl9750_wt_on (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gli_set_9750_rx_inv(struct sdhci_host *host, bool b)
{
	u32 misc_value;

	gl9750_wt_on(host);

	misc_value = sdhci_readl(host, SDHCI_GLI_9750_MISC);
	misc_value &= ~SDHCI_GLI_9750_MISC_RX_INV;
	if (b) {
		misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_RX_INV,
					 GLI_9750_MISC_RX_INV_ON);
	} else {
		misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_RX_INV,
					 GLI_9750_MISC_RX_INV_OFF);
	}
	sdhci_writel(host, misc_value, SDHCI_GLI_9750_MISC);

	gl9750_wt_off(host);
}