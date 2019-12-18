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
struct team_mode_item {int /*<<< orphan*/  list; } ;
struct team_mode {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 struct team_mode_item* __find_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct team_mode_item*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void team_mode_unregister(const struct team_mode *mode)
{
	struct team_mode_item *mitem;

	spin_lock(&mode_list_lock);
	mitem = __find_mode(mode->kind);
	if (mitem) {
		list_del_init(&mitem->list);
		kfree(mitem);
	}
	spin_unlock(&mode_list_lock);
}