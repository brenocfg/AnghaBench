#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssb_bus {struct sdio_func* host_sdio; } ;
struct sdio_func {int dummy; } ;
struct b43_wldev {TYPE_2__* dev; } ;
struct b43_sdio {void (* irq_handler ) (struct b43_wldev*) ;struct b43_wldev* irq_handler_opaque; } ;
struct TYPE_4__ {TYPE_1__* sdev; } ;
struct TYPE_3__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_sdio_interrupt_dispatcher ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int sdio_claim_irq (struct sdio_func*,int /*<<< orphan*/ ) ; 
 struct b43_sdio* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 

int b43_sdio_request_irq(struct b43_wldev *dev,
			 void (*handler)(struct b43_wldev *dev))
{
	struct ssb_bus *bus = dev->dev->sdev->bus;
	struct sdio_func *func = bus->host_sdio;
	struct b43_sdio *sdio = sdio_get_drvdata(func);
	int err;

	sdio->irq_handler_opaque = dev;
	sdio->irq_handler = handler;
	sdio_claim_host(func);
	err = sdio_claim_irq(func, b43_sdio_interrupt_dispatcher);
	sdio_release_host(func);

	return err;
}