#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int max_brightness; int /*<<< orphan*/  name; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set; } ;
struct iwl_priv {int led_registered; TYPE_3__ led; TYPE_2__* trans; TYPE_5__* hw; TYPE_1__* cfg; } ;
struct TYPE_11__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_10__ {int led_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int led_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_TPT_LEDTRIG_FL_CONNECTED ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_priv*,char*) ; 
#define  IWL_LED_BLINK 130 
#define  IWL_LED_DEFAULT 129 
 int IWL_LED_DISABLE ; 
#define  IWL_LED_RF_STATE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_create_tpt_led_trigger (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_radio_led_name (TYPE_5__*) ; 
 int /*<<< orphan*/  iwl_blink ; 
 int /*<<< orphan*/  iwl_led_blink_set ; 
 int /*<<< orphan*/  iwl_led_brightness_set ; 
 TYPE_4__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int led_classdev_register (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

void iwl_leds_init(struct iwl_priv *priv)
{
	int mode = iwlwifi_mod_params.led_mode;
	int ret;

	if (mode == IWL_LED_DISABLE) {
		IWL_INFO(priv, "Led disabled\n");
		return;
	}
	if (mode == IWL_LED_DEFAULT)
		mode = priv->cfg->led_mode;

	priv->led.name = kasprintf(GFP_KERNEL, "%s-led",
				   wiphy_name(priv->hw->wiphy));
	priv->led.brightness_set = iwl_led_brightness_set;
	priv->led.blink_set = iwl_led_blink_set;
	priv->led.max_brightness = 1;

	switch (mode) {
	case IWL_LED_DEFAULT:
		WARN_ON(1);
		break;
	case IWL_LED_BLINK:
		priv->led.default_trigger =
			ieee80211_create_tpt_led_trigger(priv->hw,
					IEEE80211_TPT_LEDTRIG_FL_CONNECTED,
					iwl_blink, ARRAY_SIZE(iwl_blink));
		break;
	case IWL_LED_RF_STATE:
		priv->led.default_trigger =
			ieee80211_get_radio_led_name(priv->hw);
		break;
	}

	ret = led_classdev_register(priv->trans->dev, &priv->led);
	if (ret) {
		kfree(priv->led.name);
		return;
	}

	priv->led_registered = true;
}