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
struct TYPE_2__ {scalar_t__ current_mode; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ IEEE1284_MODE_COMPAT ; 
 int LP_ABORT ; 
 int LP_F (int) ; 
 int /*<<< orphan*/  current ; 
 int lp_check_status (int) ; 
 TYPE_1__* lp_table ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp_wait_ready(int minor, int nonblock)
{
	int error = 0;

	/* If we're not in compatibility mode, we're ready now! */
	if (lp_table[minor].current_mode != IEEE1284_MODE_COMPAT) {
	  return (0);
	}

	do {
		error = lp_check_status (minor);
		if (error && (nonblock || (LP_F(minor) & LP_ABORT)))
			break;
		if (signal_pending (current)) {
			error = -EINTR;
			break;
		}
	} while (error);
	return error;
}