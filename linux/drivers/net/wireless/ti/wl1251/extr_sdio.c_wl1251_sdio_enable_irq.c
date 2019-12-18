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
struct wl1251 {int dummy; } ;
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_claim_irq (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  wl1251_sdio_interrupt ; 
 struct sdio_func* wl_to_func (struct wl1251*) ; 

__attribute__((used)) static void wl1251_sdio_enable_irq(struct wl1251 *wl)
{
	struct sdio_func *func = wl_to_func(wl);

	sdio_claim_host(func);
	sdio_claim_irq(func, wl1251_sdio_interrupt);
	sdio_release_host(func);
}