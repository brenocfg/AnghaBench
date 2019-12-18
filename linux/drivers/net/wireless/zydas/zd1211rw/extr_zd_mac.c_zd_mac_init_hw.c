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
typedef  int /*<<< orphan*/  u8 ;
struct zd_chip {int dummy; } ;
struct zd_mac {int /*<<< orphan*/  regdomain; int /*<<< orphan*/  lock; int /*<<< orphan*/  default_regdomain; struct zd_chip chip; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_SNIFFER ; 
 int /*<<< orphan*/  ZD_ASSERT (int) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int regulatory_hint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_disable_int (struct zd_chip*) ; 
 int zd_chip_enable_int (struct zd_chip*) ; 
 int zd_chip_init_hw (struct zd_chip*) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 
 int zd_read_regdomain (struct zd_chip*,int /*<<< orphan*/ *) ; 
 int zd_reg2alpha2 (int /*<<< orphan*/ ,char*) ; 
 int zd_set_encryption_type (struct zd_chip*,int /*<<< orphan*/ ) ; 

int zd_mac_init_hw(struct ieee80211_hw *hw)
{
	int r;
	struct zd_mac *mac = zd_hw_mac(hw);
	struct zd_chip *chip = &mac->chip;
	char alpha2[2];
	u8 default_regdomain;

	r = zd_chip_enable_int(chip);
	if (r)
		goto out;
	r = zd_chip_init_hw(chip);
	if (r)
		goto disable_int;

	ZD_ASSERT(!irqs_disabled());

	r = zd_read_regdomain(chip, &default_regdomain);
	if (r)
		goto disable_int;
	spin_lock_irq(&mac->lock);
	mac->regdomain = mac->default_regdomain = default_regdomain;
	spin_unlock_irq(&mac->lock);

	/* We must inform the device that we are doing encryption/decryption in
	 * software at the moment. */
	r = zd_set_encryption_type(chip, ENC_SNIFFER);
	if (r)
		goto disable_int;

	r = zd_reg2alpha2(mac->regdomain, alpha2);
	if (r)
		goto disable_int;

	r = regulatory_hint(hw->wiphy, alpha2);
disable_int:
	zd_chip_disable_int(chip);
out:
	return r;
}