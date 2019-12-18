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
struct zl6100_data {scalar_t__ delay; int /*<<< orphan*/  access; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static inline void zl6100_wait(const struct zl6100_data *data)
{
	if (data->delay) {
		s64 delta = ktime_us_delta(ktime_get(), data->access);
		if (delta < data->delay)
			udelay(data->delay - delta);
	}
}