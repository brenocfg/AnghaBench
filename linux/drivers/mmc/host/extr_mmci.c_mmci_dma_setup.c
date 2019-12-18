#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmci_host {int next_cookie; int use_dma; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* dma_setup ) (struct mmci_host*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct mmci_host*) ; 

void mmci_dma_setup(struct mmci_host *host)
{
	if (!host->ops || !host->ops->dma_setup)
		return;

	if (host->ops->dma_setup(host))
		return;

	/* initialize pre request cookie */
	host->next_cookie = 1;

	host->use_dma = true;
}