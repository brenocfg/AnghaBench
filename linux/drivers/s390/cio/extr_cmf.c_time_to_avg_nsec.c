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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_to_nsec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 time_to_avg_nsec(u32 value, u32 count)
{
	u64 ret;

	/* no samples yet, avoid division by 0 */
	if (count == 0)
		return 0;

	/* value comes in units of 128 µsec */
	ret = time_to_nsec(value);
	do_div(ret, count);

	return ret;
}