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
struct mmc_gpio {int cd_debounce_delay_ms; scalar_t__ ro_label; scalar_t__ cd_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 struct mmc_gpio* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (scalar_t__,size_t,char*,char*) ; 
 int strlen (char*) ; 

int mmc_gpio_alloc(struct mmc_host *host)
{
	size_t len = strlen(dev_name(host->parent)) + 4;
	struct mmc_gpio *ctx = devm_kzalloc(host->parent,
				sizeof(*ctx) + 2 * len,	GFP_KERNEL);

	if (ctx) {
		ctx->ro_label = ctx->cd_label + len;
		ctx->cd_debounce_delay_ms = 200;
		snprintf(ctx->cd_label, len, "%s cd", dev_name(host->parent));
		snprintf(ctx->ro_label, len, "%s ro", dev_name(host->parent));
		host->slot.handler_priv = ctx;
		host->slot.cd_irq = -EINVAL;
	}

	return ctx ? 0 : -ENOMEM;
}