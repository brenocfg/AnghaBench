#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_PRIORITY_CAP ; 
 long MAX_NICE ; 
 int /*<<< orphan*/  RLIMIT_NICE ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/  binder_user_error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ can_nice (TYPE_1__*,long) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  rlimit (int /*<<< orphan*/ ) ; 
 long rlimit_to_nice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_nice (TYPE_1__*,long) ; 

__attribute__((used)) static void binder_set_nice(long nice)
{
	long min_nice;

	if (can_nice(current, nice)) {
		set_user_nice(current, nice);
		return;
	}
	min_nice = rlimit_to_nice(rlimit(RLIMIT_NICE));
	binder_debug(BINDER_DEBUG_PRIORITY_CAP,
		     "%d: nice value %ld not allowed use %ld instead\n",
		      current->pid, nice, min_nice);
	set_user_nice(current, min_nice);
	if (min_nice <= MAX_NICE)
		return;
	binder_user_error("%d RLIMIT_NICE not set\n", current->pid);
}