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
struct mxs_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxs_mmc_request_done (struct mxs_mmc_host*) ; 

__attribute__((used)) static void mxs_mmc_dma_irq_callback(void *param)
{
	struct mxs_mmc_host *host = param;

	mxs_mmc_request_done(host);
}