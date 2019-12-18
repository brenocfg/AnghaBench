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
struct mv88e6xxx_chip {int /*<<< orphan*/  ppu_timer; int /*<<< orphan*/  ppu_work; int /*<<< orphan*/  ppu_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv88e6xxx_phy_ppu_reenable_timer ; 
 int /*<<< orphan*/  mv88e6xxx_phy_ppu_reenable_work ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv88e6xxx_phy_ppu_state_init(struct mv88e6xxx_chip *chip)
{
	mutex_init(&chip->ppu_mutex);
	INIT_WORK(&chip->ppu_work, mv88e6xxx_phy_ppu_reenable_work);
	timer_setup(&chip->ppu_timer, mv88e6xxx_phy_ppu_reenable_timer, 0);
}