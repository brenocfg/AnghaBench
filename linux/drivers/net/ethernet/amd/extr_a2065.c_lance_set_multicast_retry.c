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
struct lance_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct lance_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lance_set_multicast (int /*<<< orphan*/ ) ; 
 struct lance_private* lp ; 
 int /*<<< orphan*/  multicast_timer ; 

__attribute__((used)) static void lance_set_multicast_retry(struct timer_list *t)
{
	struct lance_private *lp = from_timer(lp, t, multicast_timer);

	lance_set_multicast(lp->dev);
}