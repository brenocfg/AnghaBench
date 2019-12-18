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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ num_gpio_pins; int gpio_mask; } ;
struct ath_hw {TYPE_1__ caps; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_SOC (struct ath_hw*) ; 
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath9k_hw_gpio_cfg_soc (struct ath_hw*,scalar_t__,int,char const*) ; 
 int /*<<< orphan*/  ath9k_hw_gpio_cfg_wmac (struct ath_hw*,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static void ath9k_hw_gpio_request(struct ath_hw *ah, u32 gpio, bool out,
				  const char *label, u32 ah_signal_type)
{
	WARN_ON(gpio >= ah->caps.num_gpio_pins);

	if (BIT(gpio) & ah->caps.gpio_mask)
		ath9k_hw_gpio_cfg_wmac(ah, gpio, out, ah_signal_type);
	else if (AR_SREV_SOC(ah))
		ath9k_hw_gpio_cfg_soc(ah, gpio, out, label);
	else
		WARN_ON(1);
}