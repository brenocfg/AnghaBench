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
struct igorplugusb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_INFRACODE ; 
 struct igorplugusb* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igorplugusb_cmd (struct igorplugusb*,int /*<<< orphan*/ ) ; 
 struct igorplugusb* ir ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void igorplugusb_timer(struct timer_list *t)
{
	struct igorplugusb *ir = from_timer(ir, t, timer);

	igorplugusb_cmd(ir, GET_INFRACODE);
}