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
struct brcms_timer {void (* fn ) (void*) ;int /*<<< orphan*/  name; struct brcms_timer* next; void* arg; struct brcms_info* wl; int /*<<< orphan*/  dly_wrk; } ;
struct brcms_info {struct brcms_timer* timers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _brcms_timer ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct brcms_timer* kzalloc (int,int /*<<< orphan*/ ) ; 

struct brcms_timer *brcms_init_timer(struct brcms_info *wl,
				     void (*fn) (void *arg),
				     void *arg, const char *name)
{
	struct brcms_timer *t;

	t = kzalloc(sizeof(struct brcms_timer), GFP_ATOMIC);
	if (!t)
		return NULL;

	INIT_DELAYED_WORK(&t->dly_wrk, _brcms_timer);
	t->wl = wl;
	t->fn = fn;
	t->arg = arg;
	t->next = wl->timers;
	wl->timers = t;

#ifdef DEBUG
	t->name = kstrdup(name, GFP_ATOMIC);
#endif

	return t;
}