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
struct sbmacdma {int /*<<< orphan*/ * sbdma_remptr; int /*<<< orphan*/ * sbdma_addptr; int /*<<< orphan*/  sbdma_config0; int /*<<< orphan*/  sbdma_dscrbase; int /*<<< orphan*/  sbdma_config1; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sbdma_channel_stop(struct sbmacdma *d)
{
	/*
	 * Turn off the DMA channel
	 */

	__raw_writeq(0, d->sbdma_config1);

	__raw_writeq(0, d->sbdma_dscrbase);

	__raw_writeq(0, d->sbdma_config0);

	/*
	 * Zero ring pointers
	 */

	d->sbdma_addptr = NULL;
	d->sbdma_remptr = NULL;
}