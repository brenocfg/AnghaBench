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
struct work_struct {int dummy; } ;
struct noflush_work {int /*<<< orphan*/  pw; TYPE_1__* tc; } ;
struct TYPE_2__ {int requeue_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  pool_work_complete (int /*<<< orphan*/ *) ; 
 struct noflush_work* to_noflush (struct work_struct*) ; 

__attribute__((used)) static void do_noflush_stop(struct work_struct *ws)
{
	struct noflush_work *w = to_noflush(ws);
	w->tc->requeue_mode = false;
	pool_work_complete(&w->pw);
}