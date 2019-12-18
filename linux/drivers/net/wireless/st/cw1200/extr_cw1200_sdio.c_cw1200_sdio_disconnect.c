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
struct hwbus_priv {int /*<<< orphan*/ * core; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw1200_core_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_sdio_irq_unsubscribe (struct hwbus_priv*) ; 
 int /*<<< orphan*/  kfree (struct hwbus_priv*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 struct hwbus_priv* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cw1200_sdio_disconnect(struct sdio_func *func)
{
	struct hwbus_priv *self = sdio_get_drvdata(func);

	if (self) {
		cw1200_sdio_irq_unsubscribe(self);
		if (self->core) {
			cw1200_core_release(self->core);
			self->core = NULL;
		}
		sdio_claim_host(func);
		sdio_disable_func(func);
		sdio_release_host(func);
		sdio_set_drvdata(func, NULL);
		kfree(self);
	}
}