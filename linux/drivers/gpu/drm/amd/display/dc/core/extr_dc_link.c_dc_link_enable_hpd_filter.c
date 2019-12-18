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
struct gpio_hpd_config {scalar_t__ delay_on_disconnect; scalar_t__ delay_on_connect; } ;
struct gpio {int dummy; } ;
struct dc_link {int is_hpd_filter_disabled; TYPE_1__* ctx; int /*<<< orphan*/  link_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_service; int /*<<< orphan*/  dc_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GPIO_MODE_INTERRUPT ; 
 scalar_t__ GPIO_RESULT_OK ; 
 int /*<<< orphan*/  dal_gpio_close (struct gpio*) ; 
 int /*<<< orphan*/  dal_gpio_destroy_irq (struct gpio**) ; 
 scalar_t__ dal_gpio_open (struct gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dal_irq_setup_hpd_filter (struct gpio*,struct gpio_hpd_config*) ; 
 struct gpio* get_hpd_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_hpd_filter (struct dc_link*) ; 

void dc_link_enable_hpd_filter(struct dc_link *link, bool enable)
{
	struct gpio *hpd;

	if (enable) {
		link->is_hpd_filter_disabled = false;
		program_hpd_filter(link);
	} else {
		link->is_hpd_filter_disabled = true;
		/* Obtain HPD handle */
		hpd = get_hpd_gpio(link->ctx->dc_bios, link->link_id, link->ctx->gpio_service);

		if (!hpd)
			return;

		/* Setup HPD filtering */
		if (dal_gpio_open(hpd, GPIO_MODE_INTERRUPT) == GPIO_RESULT_OK) {
			struct gpio_hpd_config config;

			config.delay_on_connect = 0;
			config.delay_on_disconnect = 0;

			dal_irq_setup_hpd_filter(hpd, &config);

			dal_gpio_close(hpd);
		} else {
			ASSERT_CRITICAL(false);
		}
		/* Release HPD handle */
		dal_gpio_destroy_irq(&hpd);
	}
}