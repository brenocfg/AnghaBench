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
struct TYPE_2__ {struct mmc_gpio* handler_priv; } ;
struct mmc_host {int /*<<< orphan*/  parent; TYPE_1__ slot; } ;
struct mmc_gpio {int override_cd_active_level; int /*<<< orphan*/  cd_gpio; int /*<<< orphan*/  cd_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOF_DIR_IN ; 
 int devm_gpio_request_one (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_set_debounce (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gpio_to_desc (unsigned int) ; 

int mmc_gpio_request_cd(struct mmc_host *host, unsigned int gpio,
			unsigned int debounce)
{
	struct mmc_gpio *ctx = host->slot.handler_priv;
	int ret;

	ret = devm_gpio_request_one(host->parent, gpio, GPIOF_DIR_IN,
				    ctx->cd_label);
	if (ret < 0)
		/*
		 * don't bother freeing memory. It might still get used by other
		 * slot functions, in any case it will be freed, when the device
		 * is destroyed.
		 */
		return ret;

	if (debounce) {
		ret = gpio_set_debounce(gpio, debounce);
		if (ret < 0)
			return ret;
	}

	ctx->override_cd_active_level = true;
	ctx->cd_gpio = gpio_to_desc(gpio);

	return 0;
}