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
 int /*<<< orphan*/  PHY_ADDR_REG ; 
 int /*<<< orphan*/  PHY_BUSY ; 
 int /*<<< orphan*/  PHY_DAT_REG ; 
 int PHY_WRITE ; 
 int arasan_phy_addr_poll (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arasan_phy_write(struct sdhci_host *host, u8 data, u8 offset)
{
	sdhci_writew(host, data, PHY_DAT_REG);
	sdhci_writew(host, (PHY_WRITE | offset), PHY_ADDR_REG);
	return arasan_phy_addr_poll(host, PHY_ADDR_REG, PHY_BUSY);
}