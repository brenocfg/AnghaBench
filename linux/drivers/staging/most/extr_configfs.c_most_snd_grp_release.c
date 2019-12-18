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
struct most_snd_grp {int /*<<< orphan*/  list; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct most_snd_grp*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct most_snd_grp* to_most_snd_grp (struct config_item*) ; 

__attribute__((used)) static void most_snd_grp_release(struct config_item *item)
{
	struct most_snd_grp *group = to_most_snd_grp(item);

	list_del(&group->list);
	kfree(group);
}