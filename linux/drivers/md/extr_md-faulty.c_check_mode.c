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
struct faulty_conf {scalar_t__* period; int /*<<< orphan*/ * counters; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int check_mode(struct faulty_conf *conf, int mode)
{
	if (conf->period[mode] == 0 &&
	    atomic_read(&conf->counters[mode]) <= 0)
		return 0; /* no failure, no decrement */


	if (atomic_dec_and_test(&conf->counters[mode])) {
		if (conf->period[mode])
			atomic_set(&conf->counters[mode], conf->period[mode]);
		return 1;
	}
	return 0;
}