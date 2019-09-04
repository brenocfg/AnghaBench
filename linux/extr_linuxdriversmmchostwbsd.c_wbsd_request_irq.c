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
struct wbsd_host {int irq; int /*<<< orphan*/  finish_tasklet; int /*<<< orphan*/  timeout_tasklet; int /*<<< orphan*/  crc_tasklet; int /*<<< orphan*/  fifo_tasklet; int /*<<< orphan*/  card_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wbsd_host*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wbsd_irq ; 
 int /*<<< orphan*/  wbsd_tasklet_card ; 
 int /*<<< orphan*/  wbsd_tasklet_crc ; 
 int /*<<< orphan*/  wbsd_tasklet_fifo ; 
 int /*<<< orphan*/  wbsd_tasklet_finish ; 
 int /*<<< orphan*/  wbsd_tasklet_timeout ; 

__attribute__((used)) static int wbsd_request_irq(struct wbsd_host *host, int irq)
{
	int ret;

	/*
	 * Set up tasklets. Must be done before requesting interrupt.
	 */
	tasklet_init(&host->card_tasklet, wbsd_tasklet_card,
			(unsigned long)host);
	tasklet_init(&host->fifo_tasklet, wbsd_tasklet_fifo,
			(unsigned long)host);
	tasklet_init(&host->crc_tasklet, wbsd_tasklet_crc,
			(unsigned long)host);
	tasklet_init(&host->timeout_tasklet, wbsd_tasklet_timeout,
			(unsigned long)host);
	tasklet_init(&host->finish_tasklet, wbsd_tasklet_finish,
			(unsigned long)host);

	/*
	 * Allocate interrupt.
	 */
	ret = request_irq(irq, wbsd_irq, IRQF_SHARED, DRIVER_NAME, host);
	if (ret)
		return ret;

	host->irq = irq;

	return 0;
}