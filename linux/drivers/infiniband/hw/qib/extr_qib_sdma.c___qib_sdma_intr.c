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
struct qib_pportdata {int /*<<< orphan*/  sdma_userpending; } ;

/* Variables and functions */
 scalar_t__ __qib_sdma_running (struct qib_pportdata*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_sdma_make_progress (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_user_sdma_send_desc (struct qib_pportdata*,int /*<<< orphan*/ *) ; 

void __qib_sdma_intr(struct qib_pportdata *ppd)
{
	if (__qib_sdma_running(ppd)) {
		qib_sdma_make_progress(ppd);
		if (!list_empty(&ppd->sdma_userpending))
			qib_user_sdma_send_desc(ppd, &ppd->sdma_userpending);
	}
}