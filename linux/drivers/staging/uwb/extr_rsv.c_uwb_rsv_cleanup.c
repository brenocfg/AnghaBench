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
struct uwb_rc {int /*<<< orphan*/  rsv_workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_rsv_remove_all (struct uwb_rc*) ; 

void uwb_rsv_cleanup(struct uwb_rc *rc)
{
	uwb_rsv_remove_all(rc);
	destroy_workqueue(rc->rsv_workq);
}