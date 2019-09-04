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
typedef  scalar_t__ u64 ;
struct regmap {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int regmap_read (struct regmap*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,unsigned long) ; 

__attribute__((used)) static inline int tc_poll_timeout(struct regmap *map, unsigned int addr,
				  unsigned int cond_mask,
				  unsigned int cond_value,
				  unsigned long sleep_us, u64 timeout_us)
{
	ktime_t timeout = ktime_add_us(ktime_get(), timeout_us);
	unsigned int val;
	int ret;

	for (;;) {
		ret = regmap_read(map, addr, &val);
		if (ret)
			break;
		if ((val & cond_mask) == cond_value)
			break;
		if (timeout_us && ktime_compare(ktime_get(), timeout) > 0) {
			ret = regmap_read(map, addr, &val);
			break;
		}
		if (sleep_us)
			usleep_range((sleep_us >> 2) + 1, sleep_us);
	}
	return ret ?: (((val & cond_mask) == cond_value) ? 0 : -ETIMEDOUT);
}