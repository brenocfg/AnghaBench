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
struct sdhci_host {TYPE_1__* data; int /*<<< orphan*/  bounce_addr; scalar_t__ bounce_buffer; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_addr_t sdhci_sdma_address(struct sdhci_host *host)
{
	if (host->bounce_buffer)
		return host->bounce_addr;
	else
		return sg_dma_address(host->data->sg);
}