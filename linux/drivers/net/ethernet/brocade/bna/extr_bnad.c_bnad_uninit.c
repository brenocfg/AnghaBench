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
struct bnad {scalar_t__ bar0; int /*<<< orphan*/ * work_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

__attribute__((used)) static void
bnad_uninit(struct bnad *bnad)
{
	if (bnad->work_q) {
		flush_workqueue(bnad->work_q);
		destroy_workqueue(bnad->work_q);
		bnad->work_q = NULL;
	}

	if (bnad->bar0)
		iounmap(bnad->bar0);
}