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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_RAW_SPINLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ss_spin ; 

__attribute__((used)) static int ss_get(void *data, u64 *val)
{
	ktime_t start, finish;
	int loops;
	int cont;
	DEFINE_RAW_SPINLOCK(ss_spin);

	loops = 1000000;
	cont = 1;

	start = ktime_get();

	while (cont) {
		raw_spin_lock(&ss_spin);
		loops--;
		if (loops == 0)
			cont = 0;
		raw_spin_unlock(&ss_spin);
	}

	finish = ktime_get();

	*val = ktime_us_delta(finish, start);

	return 0;
}