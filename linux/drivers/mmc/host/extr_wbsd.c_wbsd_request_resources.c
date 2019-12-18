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
struct wbsd_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wbsd_request_dma (struct wbsd_host*,int) ; 
 int wbsd_request_irq (struct wbsd_host*,int) ; 
 int wbsd_request_region (struct wbsd_host*,int) ; 

__attribute__((used)) static int wbsd_request_resources(struct wbsd_host *host,
	int base, int irq, int dma)
{
	int ret;

	/*
	 * Allocate I/O ports.
	 */
	ret = wbsd_request_region(host, base);
	if (ret)
		return ret;

	/*
	 * Allocate interrupt.
	 */
	ret = wbsd_request_irq(host, irq);
	if (ret)
		return ret;

	/*
	 * Allocate DMA.
	 */
	wbsd_request_dma(host, dma);

	return 0;
}