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
struct wiimote_data {int dummy; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct wiimote_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 struct wiimote_data* wdata ; 
 int /*<<< orphan*/  wiimote_schedule (struct wiimote_data*) ; 

__attribute__((used)) static void wiimote_init_timeout(struct timer_list *t)
{
	struct wiimote_data *wdata = from_timer(wdata, t, timer);

	wiimote_schedule(wdata);
}