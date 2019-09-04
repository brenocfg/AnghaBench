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
struct mv88e6xxx_chip {int /*<<< orphan*/  ppu_mutex; int /*<<< orphan*/  ppu_timer; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv88e6xxx_phy_ppu_access_put(struct mv88e6xxx_chip *chip)
{
	/* Schedule a timer to re-enable the PHY polling unit. */
	mod_timer(&chip->ppu_timer, jiffies + msecs_to_jiffies(10));
	mutex_unlock(&chip->ppu_mutex);
}