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
struct fc_exch {int /*<<< orphan*/  ex_refcnt; int /*<<< orphan*/  timeout_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_EXCH_DBG (struct fc_exch*,char*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fc_exch_timer_cancel(struct fc_exch *ep)
{
	if (cancel_delayed_work(&ep->timeout_work)) {
		FC_EXCH_DBG(ep, "Exchange timer canceled\n");
		atomic_dec(&ep->ex_refcnt); /* drop hold for timer */
	}
}