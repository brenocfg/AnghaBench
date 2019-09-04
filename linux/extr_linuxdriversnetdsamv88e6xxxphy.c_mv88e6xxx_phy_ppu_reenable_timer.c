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
struct timer_list {int dummy; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  ppu_work; } ;

/* Variables and functions */
 struct mv88e6xxx_chip* chip ; 
 struct mv88e6xxx_chip* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppu_timer ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv88e6xxx_phy_ppu_reenable_timer(struct timer_list *t)
{
	struct mv88e6xxx_chip *chip = from_timer(chip, t, ppu_timer);

	schedule_work(&chip->ppu_work);
}