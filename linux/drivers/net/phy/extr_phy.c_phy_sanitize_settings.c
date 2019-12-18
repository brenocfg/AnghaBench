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
struct phy_setting {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct phy_device {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 struct phy_setting* phy_find_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phy_sanitize_settings(struct phy_device *phydev)
{
	const struct phy_setting *setting;

	setting = phy_find_valid(phydev->speed, phydev->duplex,
				 phydev->supported);
	if (setting) {
		phydev->speed = setting->speed;
		phydev->duplex = setting->duplex;
	} else {
		/* We failed to find anything (no supported speeds?) */
		phydev->speed = SPEED_UNKNOWN;
		phydev->duplex = DUPLEX_UNKNOWN;
	}
}