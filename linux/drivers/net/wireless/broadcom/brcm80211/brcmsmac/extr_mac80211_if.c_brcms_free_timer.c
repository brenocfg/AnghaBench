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
struct brcms_timer {struct brcms_timer* next; struct brcms_timer* name; struct brcms_info* wl; } ;
struct brcms_info {struct brcms_timer* timers; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_del_timer (struct brcms_timer*) ; 
 int /*<<< orphan*/  kfree (struct brcms_timer*) ; 

void brcms_free_timer(struct brcms_timer *t)
{
	struct brcms_info *wl = t->wl;
	struct brcms_timer *tmp;

	/* delete the timer in case it is active */
	brcms_del_timer(t);

	if (wl->timers == t) {
		wl->timers = wl->timers->next;
#ifdef DEBUG
		kfree(t->name);
#endif
		kfree(t);
		return;

	}

	tmp = wl->timers;
	while (tmp) {
		if (tmp->next == t) {
			tmp->next = t->next;
#ifdef DEBUG
			kfree(t->name);
#endif
			kfree(t);
			return;
		}
		tmp = tmp->next;
	}

}