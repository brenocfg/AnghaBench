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
struct hwbus_priv {scalar_t__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw1200_irq_handler (scalar_t__) ; 
 struct hwbus_priv* sdio_get_drvdata (struct sdio_func*) ; 

__attribute__((used)) static void cw1200_sdio_irq_handler(struct sdio_func *func)
{
	struct hwbus_priv *self = sdio_get_drvdata(func);

	/* note:  sdio_host already claimed here. */
	if (self->core)
		cw1200_irq_handler(self->core);
}