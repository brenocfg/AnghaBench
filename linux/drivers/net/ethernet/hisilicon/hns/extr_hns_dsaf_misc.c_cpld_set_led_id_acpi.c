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
struct hns_mac_cb {int /*<<< orphan*/  dev; int /*<<< orphan*/  mac_id; } ;
typedef  enum hnae_led_state { ____Placeholder_hnae_led_state } hnae_led_state ;

/* Variables and functions */
 int /*<<< orphan*/  CPLD_LED_DEFAULT_VALUE ; 
 int /*<<< orphan*/  CPLD_LED_ON_VALUE ; 
 int EINVAL ; 
#define  HNAE_LED_ACTIVE 129 
#define  HNAE_LED_INACTIVE 128 
 int /*<<< orphan*/  HNS_OP_LOCATE_LED_SET_FUNC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hns_dsaf_acpi_locate_ledctrl_by_port (struct hns_mac_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpld_set_led_id_acpi(struct hns_mac_cb *mac_cb,
				enum hnae_led_state status)
{
	switch (status) {
	case HNAE_LED_ACTIVE:
		hns_dsaf_acpi_locate_ledctrl_by_port(mac_cb,
						     HNS_OP_LOCATE_LED_SET_FUNC,
						     CPLD_LED_ON_VALUE,
						     mac_cb->mac_id);
		break;
	case HNAE_LED_INACTIVE:
		hns_dsaf_acpi_locate_ledctrl_by_port(mac_cb,
						     HNS_OP_LOCATE_LED_SET_FUNC,
						     CPLD_LED_DEFAULT_VALUE,
						     mac_cb->mac_id);
		break;
	default:
		dev_err(mac_cb->dev, "invalid led state: %d!", status);
		return -EINVAL;
	}

	return 0;
}