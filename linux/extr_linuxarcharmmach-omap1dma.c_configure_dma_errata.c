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

/* Variables and functions */
 int /*<<< orphan*/  DMA_ERRATA_3_3 ; 
 int /*<<< orphan*/  SET_DMA_ERRATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_is_omap15xx () ; 

__attribute__((used)) static unsigned configure_dma_errata(void)
{
	unsigned errata = 0;

	/*
	 * Erratum 3.2/3.3: sometimes 0 is returned if CSAC/CDAC is
	 * read before the DMA controller finished disabling the channel.
	 */
	if (!cpu_is_omap15xx())
		SET_DMA_ERRATA(DMA_ERRATA_3_3);

	return errata;
}