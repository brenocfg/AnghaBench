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
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tmio_mmc_do_data_irq (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  uniphier_sd_dma_endisable (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uniphier_sd_external_dma_dataend(struct tmio_mmc_host *host)
{
	uniphier_sd_dma_endisable(host, 0);

	tmio_mmc_do_data_irq(host);
}