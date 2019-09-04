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
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O2_SD_HW_TUNING_DISABLE ; 
 int /*<<< orphan*/  O2_SD_VENDOR_SETTING ; 
 int /*<<< orphan*/  sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_o2_set_tuning_mode(struct sdhci_host *host)
{
	u16 reg;

	/* enable hardware tuning */
	reg = sdhci_readw(host, O2_SD_VENDOR_SETTING);
	reg &= ~O2_SD_HW_TUNING_DISABLE;
	sdhci_writew(host, reg, O2_SD_VENDOR_SETTING);
}