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
struct sdio_func {int dummy; } ;
struct b43_wldev {int dummy; } ;
struct b43_sdio {int /*<<< orphan*/  (* irq_handler ) (struct b43_wldev*) ;struct b43_wldev* irq_handler_opaque; } ;

/* Variables and functions */
 scalar_t__ B43_STAT_STARTED ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 struct b43_sdio* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  stub1 (struct b43_wldev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void b43_sdio_interrupt_dispatcher(struct sdio_func *func)
{
	struct b43_sdio *sdio = sdio_get_drvdata(func);
	struct b43_wldev *dev = sdio->irq_handler_opaque;

	if (unlikely(b43_status(dev) < B43_STAT_STARTED))
		return;

	sdio_release_host(func);
	sdio->irq_handler(dev);
	sdio_claim_host(func);
}