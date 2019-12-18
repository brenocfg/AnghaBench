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
struct mmci_host {TYPE_1__* ops; int /*<<< orphan*/  use_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_error ) (struct mmci_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mmci_host*) ; 

void mmci_dma_error(struct mmci_host *host)
{
	if (!host->use_dma)
		return;

	if (host->ops && host->ops->dma_error)
		host->ops->dma_error(host);
}