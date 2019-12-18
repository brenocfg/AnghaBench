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
struct locomokbd {int dummy; } ;

/* Variables and functions */
 struct locomokbd* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct locomokbd* locomokbd ; 
 int /*<<< orphan*/  locomokbd_scankeyboard (struct locomokbd*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void locomokbd_timer_callback(struct timer_list *t)
{
	struct locomokbd *locomokbd = from_timer(locomokbd, t, timer);

	locomokbd_scankeyboard(locomokbd);
}