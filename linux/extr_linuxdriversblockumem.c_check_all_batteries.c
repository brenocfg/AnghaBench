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
struct cardinfo {int flags; scalar_t__ Active; int check_batteries; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int UM_FLAG_NO_BATT ; 
 struct cardinfo* cards ; 
 int /*<<< orphan*/  check_batteries (struct cardinfo*) ; 
 int /*<<< orphan*/  init_battery_timer () ; 
 int num_cards ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_all_batteries(struct timer_list *unused)
{
	int i;

	for (i = 0; i < num_cards; i++)
		if (!(cards[i].flags & UM_FLAG_NO_BATT)) {
			struct cardinfo *card = &cards[i];
			spin_lock_bh(&card->lock);
			if (card->Active >= 0)
				card->check_batteries = 1;
			else
				check_batteries(card);
			spin_unlock_bh(&card->lock);
		}

	init_battery_timer();
}