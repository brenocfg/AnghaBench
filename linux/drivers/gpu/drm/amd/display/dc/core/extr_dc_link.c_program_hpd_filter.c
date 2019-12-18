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
struct gpio_hpd_config {int delay_on_connect; int delay_on_disconnect; } ;
struct gpio {int dummy; } ;
struct dc_link {int connector_signal; TYPE_1__* ctx; int /*<<< orphan*/  link_id; scalar_t__ is_hpd_filter_disabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_service; int /*<<< orphan*/  dc_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GPIO_MODE_INTERRUPT ; 
 scalar_t__ GPIO_RESULT_OK ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 134 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 133 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 132 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 131 
#define  SIGNAL_TYPE_EDP 130 
#define  SIGNAL_TYPE_HDMI_TYPE_A 129 
#define  SIGNAL_TYPE_LVDS 128 
 int /*<<< orphan*/  dal_gpio_close (struct gpio*) ; 
 int /*<<< orphan*/  dal_gpio_destroy_irq (struct gpio**) ; 
 scalar_t__ dal_gpio_open (struct gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dal_irq_setup_hpd_filter (struct gpio*,struct gpio_hpd_config*) ; 
 struct gpio* get_hpd_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool program_hpd_filter(
	const struct dc_link *link)
{
	bool result = false;

	struct gpio *hpd;

	int delay_on_connect_in_ms = 0;
	int delay_on_disconnect_in_ms = 0;

	if (link->is_hpd_filter_disabled)
		return false;
	/* Verify feature is supported */
	switch (link->connector_signal) {
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
	case SIGNAL_TYPE_DVI_DUAL_LINK:
	case SIGNAL_TYPE_HDMI_TYPE_A:
		/* Program hpd filter */
		delay_on_connect_in_ms = 500;
		delay_on_disconnect_in_ms = 100;
		break;
	case SIGNAL_TYPE_DISPLAY_PORT:
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
		/* Program hpd filter to allow DP signal to settle */
		/* 500:	not able to detect MST <-> SST switch as HPD is low for
		 * 	only 100ms on DELL U2413
		 * 0:	some passive dongle still show aux mode instead of i2c
		 * 20-50:not enough to hide bouncing HPD with passive dongle.
		 * 	also see intermittent i2c read issues.
		 */
		delay_on_connect_in_ms = 80;
		delay_on_disconnect_in_ms = 0;
		break;
	case SIGNAL_TYPE_LVDS:
	case SIGNAL_TYPE_EDP:
	default:
		/* Don't program hpd filter */
		return false;
	}

	/* Obtain HPD handle */
	hpd = get_hpd_gpio(link->ctx->dc_bios, link->link_id, link->ctx->gpio_service);

	if (!hpd)
		return result;

	/* Setup HPD filtering */
	if (dal_gpio_open(hpd, GPIO_MODE_INTERRUPT) == GPIO_RESULT_OK) {
		struct gpio_hpd_config config;

		config.delay_on_connect = delay_on_connect_in_ms;
		config.delay_on_disconnect = delay_on_disconnect_in_ms;

		dal_irq_setup_hpd_filter(hpd, &config);

		dal_gpio_close(hpd);

		result = true;
	} else {
		ASSERT_CRITICAL(false);
	}

	/* Release HPD handle */
	dal_gpio_destroy_irq(&hpd);

	return result;
}