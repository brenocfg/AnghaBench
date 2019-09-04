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
typedef  int /*<<< orphan*/  modem_info ;

/* Variables and functions */
 int /*<<< orphan*/  RESULT_NO_CARRIER ; 
 int /*<<< orphan*/ * from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * info ; 
 int /*<<< orphan*/  isdn_tty_modem_result (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nc_timer ; 

__attribute__((used)) static void
isdn_tty_modem_do_ncarrier(struct timer_list *t)
{
	modem_info *info = from_timer(info, t, nc_timer);
	isdn_tty_modem_result(RESULT_NO_CARRIER, info);
}