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
typedef  scalar_t__ u16 ;
struct et8ek8_reglist {scalar_t__ type; } ;
struct et8ek8_meta_reglist {TYPE_1__* reglist; } ;
struct TYPE_2__ {struct et8ek8_reglist* ptr; } ;

/* Variables and functions */

__attribute__((used)) static struct et8ek8_reglist *et8ek8_reglist_find_type(
		struct et8ek8_meta_reglist *meta,
		u16 type)
{
	struct et8ek8_reglist **next = &meta->reglist[0].ptr;

	while (*next) {
		if ((*next)->type == type)
			return *next;

		next++;
	}

	return NULL;
}