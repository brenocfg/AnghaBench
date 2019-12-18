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
struct ath9k_htc_priv {TYPE_1__* ah; } ;
struct TYPE_2__ {scalar_t__ rfkill_polarity; int /*<<< orphan*/  rfkill_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 scalar_t__ ath9k_hw_gpio_get (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath_is_rfkill_set(struct ath9k_htc_priv *priv)
{
	bool is_blocked;

	ath9k_htc_ps_wakeup(priv);
	is_blocked = ath9k_hw_gpio_get(priv->ah, priv->ah->rfkill_gpio) ==
						 priv->ah->rfkill_polarity;
	ath9k_htc_ps_restore(priv);

	return is_blocked;
}