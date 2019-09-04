#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ pm_message_t ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_pr_dbg (char*,char*,char*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  pm_verb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpm_show_time(ktime_t starttime, pm_message_t state, int error,
			  const char *info)
{
	ktime_t calltime;
	u64 usecs64;
	int usecs;

	calltime = ktime_get();
	usecs64 = ktime_to_ns(ktime_sub(calltime, starttime));
	do_div(usecs64, NSEC_PER_USEC);
	usecs = usecs64;
	if (usecs == 0)
		usecs = 1;

	pm_pr_dbg("%s%s%s of devices %s after %ld.%03ld msecs\n",
		  info ?: "", info ? " " : "", pm_verb(state.event),
		  error ? "aborted" : "complete",
		  usecs / USEC_PER_MSEC, usecs % USEC_PER_MSEC);
}