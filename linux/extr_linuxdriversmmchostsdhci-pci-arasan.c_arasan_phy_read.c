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
typedef  int u8 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int DATA_MASK ; 
 int /*<<< orphan*/  PHY_ADDR_REG ; 
 int /*<<< orphan*/  PHY_BUSY ; 
 int /*<<< orphan*/  PHY_DAT_REG ; 
 int arasan_phy_addr_poll (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arasan_phy_read(struct sdhci_host *host, u8 offset, u8 *data)
{
	int ret;

	sdhci_writew(host, 0, PHY_DAT_REG);
	sdhci_writew(host, offset, PHY_ADDR_REG);
	ret = arasan_phy_addr_poll(host, PHY_ADDR_REG, PHY_BUSY);

	/* Masking valid data bits */
	*data = sdhci_readw(host, PHY_DAT_REG) & DATA_MASK;
	return ret;
}