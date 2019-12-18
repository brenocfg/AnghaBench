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
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_2__ {struct list_head* next; } ;
struct wil6210_priv {int /*<<< orphan*/  wmi_ev_lock; TYPE_1__ pending_wmi_ev; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (struct list_head*) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct list_head *next_wmi_ev(struct wil6210_priv *wil)
{
	ulong flags;
	struct list_head *ret = NULL;

	spin_lock_irqsave(&wil->wmi_ev_lock, flags);

	if (!list_empty(&wil->pending_wmi_ev)) {
		ret = wil->pending_wmi_ev.next;
		list_del(ret);
	}

	spin_unlock_irqrestore(&wil->wmi_ev_lock, flags);

	return ret;
}