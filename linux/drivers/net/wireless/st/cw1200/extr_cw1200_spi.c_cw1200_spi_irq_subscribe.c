#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hwbus_priv {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cw1200_spi_irq_handler ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hwbus_priv*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct hwbus_priv*) ; 

__attribute__((used)) static int cw1200_spi_irq_subscribe(struct hwbus_priv *self)
{
	int ret;

	pr_debug("SW IRQ subscribe\n");

	ret = request_threaded_irq(self->func->irq, NULL,
				   cw1200_spi_irq_handler,
				   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
				   "cw1200_wlan_irq", self);
	if (WARN_ON(ret < 0))
		goto exit;

	ret = enable_irq_wake(self->func->irq);
	if (WARN_ON(ret))
		goto free_irq;

	return 0;

free_irq:
	free_irq(self->func->irq, self);
exit:
	return ret;
}