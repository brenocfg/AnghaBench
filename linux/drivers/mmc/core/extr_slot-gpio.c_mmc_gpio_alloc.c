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
struct TYPE_2__ {int /*<<< orphan*/  cd_irq; struct mmc_gpio* handler_priv; } ;
struct mmc_host {TYPE_1__ slot; int /*<<< orphan*/  parent; } ;
struct mmc_gpio {int cd_debounce_delay_ms; void* ro_label; void* cd_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 void* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mmc_gpio* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mmc_gpio_alloc(struct mmc_host *host)
{
	struct mmc_gpio *ctx = devm_kzalloc(host->parent,
					    sizeof(*ctx), GFP_KERNEL);

	if (ctx) {
		ctx->cd_debounce_delay_ms = 200;
		ctx->cd_label = devm_kasprintf(host->parent, GFP_KERNEL,
				"%s cd", dev_name(host->parent));
		if (!ctx->cd_label)
			return -ENOMEM;
		ctx->ro_label = devm_kasprintf(host->parent, GFP_KERNEL,
				"%s ro", dev_name(host->parent));
		if (!ctx->ro_label)
			return -ENOMEM;
		host->slot.handler_priv = ctx;
		host->slot.cd_irq = -EINVAL;
	}

	return ctx ? 0 : -ENOMEM;
}