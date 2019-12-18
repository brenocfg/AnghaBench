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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct c4iw_ep {TYPE_1__ com; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stop_ep_timer(struct c4iw_ep *ep)
{
	pr_debug("ep %p stopping\n", ep);
	del_timer_sync(&ep->timer);
	if (!test_and_set_bit(TIMEOUT, &ep->com.flags)) {
		c4iw_put_ep(&ep->com);
		return 0;
	}
	return 1;
}