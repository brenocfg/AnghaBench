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
struct wbsd_host {int /*<<< orphan*/  finish_tasklet; int /*<<< orphan*/  timeout_tasklet; int /*<<< orphan*/  crc_tasklet; int /*<<< orphan*/  fifo_tasklet; int /*<<< orphan*/  card_tasklet; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct wbsd_host*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void  wbsd_release_irq(struct wbsd_host *host)
{
	if (!host->irq)
		return;

	free_irq(host->irq, host);

	host->irq = 0;

	tasklet_kill(&host->card_tasklet);
	tasklet_kill(&host->fifo_tasklet);
	tasklet_kill(&host->crc_tasklet);
	tasklet_kill(&host->timeout_tasklet);
	tasklet_kill(&host->finish_tasklet);
}