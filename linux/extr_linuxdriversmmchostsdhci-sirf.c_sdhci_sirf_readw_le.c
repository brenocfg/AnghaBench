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
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int SDHCI_HOST_VERSION ; 
 int /*<<< orphan*/  SDHCI_SPEC_300 ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 sdhci_sirf_readw_le(struct sdhci_host *host, int reg)
{
	u16 ret = 0;

	ret = readw(host->ioaddr + reg);

	if (unlikely(reg == SDHCI_HOST_VERSION)) {
		ret = readw(host->ioaddr + SDHCI_HOST_VERSION);
		ret |= SDHCI_SPEC_300;
	}

	return ret;
}