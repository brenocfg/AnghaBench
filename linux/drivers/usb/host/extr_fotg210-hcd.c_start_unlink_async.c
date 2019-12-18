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
struct fotg210_qh {scalar_t__ qh_state; int needs_rescan; } ;
struct fotg210_hcd {int dummy; } ;

/* Variables and functions */
 scalar_t__ QH_STATE_COMPLETING ; 
 scalar_t__ QH_STATE_LINKED ; 
 int /*<<< orphan*/  single_unlink_async (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  start_iaa_cycle (struct fotg210_hcd*,int) ; 

__attribute__((used)) static void start_unlink_async(struct fotg210_hcd *fotg210,
		struct fotg210_qh *qh)
{
	/*
	 * If the QH isn't linked then there's nothing we can do
	 * unless we were called during a giveback, in which case
	 * qh_completions() has to deal with it.
	 */
	if (qh->qh_state != QH_STATE_LINKED) {
		if (qh->qh_state == QH_STATE_COMPLETING)
			qh->needs_rescan = 1;
		return;
	}

	single_unlink_async(fotg210, qh);
	start_iaa_cycle(fotg210, false);
}