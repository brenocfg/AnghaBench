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
 int /*<<< orphan*/  wbsd_release_dma (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_release_irq (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_release_regions (struct wbsd_host*) ; 

__attribute__((used)) static void wbsd_release_resources(struct wbsd_host *host)
{
	wbsd_release_dma(host);
	wbsd_release_irq(host);
	wbsd_release_regions(host);
}