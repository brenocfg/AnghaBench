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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct timespec64 {int dummy; } ;

/* Variables and functions */
 int UINT_MAX ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int timespec64_to_ns (struct timespec64*) ; 

__attribute__((used)) static unsigned int mmc_test_rate(uint64_t bytes, struct timespec64 *ts)
{
	uint64_t ns;

	ns = timespec64_to_ns(ts);
	bytes *= 1000000000;

	while (ns > UINT_MAX) {
		bytes >>= 1;
		ns >>= 1;
	}

	if (!ns)
		return 0;

	do_div(bytes, (uint32_t)ns);

	return bytes;
}