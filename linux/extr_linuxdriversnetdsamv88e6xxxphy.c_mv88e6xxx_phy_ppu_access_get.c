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
struct mv88e6xxx_chip {int ppu_disabled; int /*<<< orphan*/  ppu_timer; int /*<<< orphan*/  ppu_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_phy_ppu_disable (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_phy_ppu_access_get(struct mv88e6xxx_chip *chip)
{
	int ret;

	mutex_lock(&chip->ppu_mutex);

	/* If the PHY polling unit is enabled, disable it so that
	 * we can access the PHY registers.  If it was already
	 * disabled, cancel the timer that is going to re-enable
	 * it.
	 */
	if (!chip->ppu_disabled) {
		ret = mv88e6xxx_phy_ppu_disable(chip);
		if (ret < 0) {
			mutex_unlock(&chip->ppu_mutex);
			return ret;
		}
		chip->ppu_disabled = 1;
	} else {
		del_timer(&chip->ppu_timer);
		ret = 0;
	}

	return ret;
}