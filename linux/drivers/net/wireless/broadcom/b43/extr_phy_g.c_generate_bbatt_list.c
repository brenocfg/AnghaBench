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
struct b43_wldev {int dummy; } ;
struct b43_bbatt_list {int max_val; scalar_t__ min_val; int /*<<< orphan*/  len; struct b43_bbatt const* list; } ;
struct b43_bbatt {int att; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct b43_bbatt const*) ; 

__attribute__((used)) static void generate_bbatt_list(struct b43_wldev *dev,
				struct b43_bbatt_list *list)
{
	static const struct b43_bbatt bbatt_0[] = {
		{.att = 0,},
		{.att = 1,},
		{.att = 2,},
		{.att = 3,},
		{.att = 4,},
		{.att = 5,},
		{.att = 6,},
		{.att = 7,},
		{.att = 8,},
	};

	list->list = bbatt_0;
	list->len = ARRAY_SIZE(bbatt_0);
	list->min_val = 0;
	list->max_val = 8;
}