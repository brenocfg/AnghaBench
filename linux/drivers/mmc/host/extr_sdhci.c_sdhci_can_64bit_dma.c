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
struct sdhci_host {scalar_t__ version; int caps; scalar_t__ v4_mode; } ;

/* Variables and functions */
 int SDHCI_CAN_64BIT ; 
 int SDHCI_CAN_64BIT_V4 ; 
 scalar_t__ SDHCI_SPEC_410 ; 

__attribute__((used)) static inline bool sdhci_can_64bit_dma(struct sdhci_host *host)
{
	/*
	 * According to SD Host Controller spec v4.10, bit[27] added from
	 * version 4.10 in Capabilities Register is used as 64-bit System
	 * Address support for V4 mode.
	 */
	if (host->version >= SDHCI_SPEC_410 && host->v4_mode)
		return host->caps & SDHCI_CAN_64BIT_V4;

	return host->caps & SDHCI_CAN_64BIT;
}