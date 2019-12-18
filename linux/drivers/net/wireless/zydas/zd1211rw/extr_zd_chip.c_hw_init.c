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
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int hw_init_hmac (struct zd_chip*) ; 
 int hw_reset_phy (struct zd_chip*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int set_beacon_interval (struct zd_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 

__attribute__((used)) static int hw_init(struct zd_chip *chip)
{
	int r;

	dev_dbg_f(zd_chip_dev(chip), "\n");
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = hw_reset_phy(chip);
	if (r)
		return r;

	r = hw_init_hmac(chip);
	if (r)
		return r;

	return set_beacon_interval(chip, 100, 0, NL80211_IFTYPE_UNSPECIFIED);
}