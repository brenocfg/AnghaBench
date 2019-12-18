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
struct b43_sdio {int /*<<< orphan*/  ssb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct b43_sdio*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 struct b43_sdio* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_bus_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_sdio_remove(struct sdio_func *func)
{
	struct b43_sdio *sdio = sdio_get_drvdata(func);

	ssb_bus_unregister(&sdio->ssb);
	sdio_claim_host(func);
	sdio_disable_func(func);
	sdio_release_host(func);
	kfree(sdio);
	sdio_set_drvdata(func, NULL);
}