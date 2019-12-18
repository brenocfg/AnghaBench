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
struct rvu {int /*<<< orphan*/ * flr_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rvu_flr_wq_destroy(struct rvu *rvu)
{
	if (rvu->flr_wq) {
		flush_workqueue(rvu->flr_wq);
		destroy_workqueue(rvu->flr_wq);
		rvu->flr_wq = NULL;
	}
}