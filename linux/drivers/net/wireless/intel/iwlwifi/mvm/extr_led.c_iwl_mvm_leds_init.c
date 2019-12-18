#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int max_brightness; int /*<<< orphan*/  name; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  brightness_set; } ;
struct iwl_mvm {int /*<<< orphan*/  init_status; TYPE_2__ led; TYPE_1__* trans; TYPE_4__* hw; } ;
struct TYPE_8__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_7__ {int led_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_mvm*,char*) ; 
#define  IWL_LED_BLINK 131 
#define  IWL_LED_DEFAULT 130 
#define  IWL_LED_DISABLE 129 
#define  IWL_LED_RF_STATE 128 
 int /*<<< orphan*/  IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE ; 
 int /*<<< orphan*/  ieee80211_get_radio_led_name (TYPE_4__*) ; 
 int /*<<< orphan*/  iwl_led_brightness_set ; 
 TYPE_3__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int led_classdev_register (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

int iwl_mvm_leds_init(struct iwl_mvm *mvm)
{
	int mode = iwlwifi_mod_params.led_mode;
	int ret;

	switch (mode) {
	case IWL_LED_BLINK:
		IWL_ERR(mvm, "Blink led mode not supported, used default\n");
		/* fall through */
	case IWL_LED_DEFAULT:
	case IWL_LED_RF_STATE:
		mode = IWL_LED_RF_STATE;
		break;
	case IWL_LED_DISABLE:
		IWL_INFO(mvm, "Led disabled\n");
		return 0;
	default:
		return -EINVAL;
	}

	mvm->led.name = kasprintf(GFP_KERNEL, "%s-led",
				   wiphy_name(mvm->hw->wiphy));
	mvm->led.brightness_set = iwl_led_brightness_set;
	mvm->led.max_brightness = 1;

	if (mode == IWL_LED_RF_STATE)
		mvm->led.default_trigger =
			ieee80211_get_radio_led_name(mvm->hw);

	ret = led_classdev_register(mvm->trans->dev, &mvm->led);
	if (ret) {
		kfree(mvm->led.name);
		IWL_INFO(mvm, "Failed to enable led\n");
		return ret;
	}

	mvm->init_status |= IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE;
	return 0;
}