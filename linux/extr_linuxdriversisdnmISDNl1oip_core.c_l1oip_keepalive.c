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
struct timer_list {int dummy; } ;
struct l1oip {int /*<<< orphan*/  workq; } ;

/* Variables and functions */
 struct l1oip* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct l1oip* hc ; 
 int /*<<< orphan*/  keep_tl ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1oip_keepalive(struct timer_list *t)
{
	struct l1oip *hc = from_timer(hc, t, keep_tl);

	schedule_work(&hc->workq);
}