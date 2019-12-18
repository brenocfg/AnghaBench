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
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  esdhc_readw_fixup (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

__attribute__((used)) static u16 esdhc_le_readw(struct sdhci_host *host, int reg)
{
	u16 ret;
	u32 value;
	int base = reg & ~0x3;

	value = ioread32(host->ioaddr + base);
	ret = esdhc_readw_fixup(host, reg, value);
	return ret;
}