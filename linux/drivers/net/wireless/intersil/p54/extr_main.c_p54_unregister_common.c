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
struct p54_common {int registered; int /*<<< orphan*/  eeprom_mutex; int /*<<< orphan*/  conf_mutex; } ;
struct ieee80211_hw {struct p54_common* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54_unregister_leds (struct p54_common*) ; 

void p54_unregister_common(struct ieee80211_hw *dev)
{
	struct p54_common *priv = dev->priv;

	if (priv->registered) {
		priv->registered = false;
#ifdef CONFIG_P54_LEDS
		p54_unregister_leds(priv);
#endif /* CONFIG_P54_LEDS */
		ieee80211_unregister_hw(dev);
	}

	mutex_destroy(&priv->conf_mutex);
	mutex_destroy(&priv->eeprom_mutex);
}