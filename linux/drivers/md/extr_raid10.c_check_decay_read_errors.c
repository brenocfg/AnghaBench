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
struct mddev {int dummy; } ;
struct md_rdev {long last_read_error; int /*<<< orphan*/  read_errors; } ;
typedef  int /*<<< orphan*/  read_errors ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned int) ; 
 long ktime_get_seconds () ; 

__attribute__((used)) static void check_decay_read_errors(struct mddev *mddev, struct md_rdev *rdev)
{
	long cur_time_mon;
	unsigned long hours_since_last;
	unsigned int read_errors = atomic_read(&rdev->read_errors);

	cur_time_mon = ktime_get_seconds();

	if (rdev->last_read_error == 0) {
		/* first time we've seen a read error */
		rdev->last_read_error = cur_time_mon;
		return;
	}

	hours_since_last = (long)(cur_time_mon -
			    rdev->last_read_error) / 3600;

	rdev->last_read_error = cur_time_mon;

	/*
	 * if hours_since_last is > the number of bits in read_errors
	 * just set read errors to 0. We do this to avoid
	 * overflowing the shift of read_errors by hours_since_last.
	 */
	if (hours_since_last >= 8 * sizeof(read_errors))
		atomic_set(&rdev->read_errors, 0);
	else
		atomic_set(&rdev->read_errors, read_errors >> hours_since_last);
}