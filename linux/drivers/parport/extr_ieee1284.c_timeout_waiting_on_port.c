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
struct parport {int dummy; } ;

/* Variables and functions */
 struct parport* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_ieee1284_wakeup (struct parport*) ; 
 struct parport* port ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void timeout_waiting_on_port (struct timer_list *t)
{
	struct parport *port = from_timer(port, t, timer);

	parport_ieee1284_wakeup (port);
}