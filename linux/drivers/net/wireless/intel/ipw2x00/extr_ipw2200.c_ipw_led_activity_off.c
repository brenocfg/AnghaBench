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
typedef  int /*<<< orphan*/  u32 ;
struct ipw_priv {int config; int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  led_activity_off; } ;

/* Variables and functions */
 int CFG_NO_LED ; 
 int /*<<< orphan*/  IPW_DEBUG_LED (char*,...) ; 
 int /*<<< orphan*/  IPW_EVENT_REG ; 
 int STATUS_LED_ACT_ON ; 
 int /*<<< orphan*/  ipw_read_reg32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_register_toggle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_write_reg32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipw_led_activity_off(struct ipw_priv *priv)
{
	unsigned long flags;
	u32 led;

	if (priv->config & CFG_NO_LED)
		return;

	spin_lock_irqsave(&priv->lock, flags);

	if (priv->status & STATUS_LED_ACT_ON) {
		led = ipw_read_reg32(priv, IPW_EVENT_REG);
		led &= priv->led_activity_off;

		led = ipw_register_toggle(led);

		IPW_DEBUG_LED("Reg: 0x%08X\n", led);
		ipw_write_reg32(priv, IPW_EVENT_REG, led);

		IPW_DEBUG_LED("Activity LED Off\n");

		priv->status &= ~STATUS_LED_ACT_ON;
	}

	spin_unlock_irqrestore(&priv->lock, flags);
}