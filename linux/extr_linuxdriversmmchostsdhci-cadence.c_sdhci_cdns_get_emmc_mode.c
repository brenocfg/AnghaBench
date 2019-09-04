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
struct sdhci_cdns_priv {scalar_t__ hrs_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SDHCI_CDNS_HRS06 ; 
 int /*<<< orphan*/  SDHCI_CDNS_HRS06_MODE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static u32 sdhci_cdns_get_emmc_mode(struct sdhci_cdns_priv *priv)
{
	u32 tmp;

	tmp = readl(priv->hrs_addr + SDHCI_CDNS_HRS06);
	return FIELD_GET(SDHCI_CDNS_HRS06_MODE, tmp);
}