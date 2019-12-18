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
struct loopback_test {int mask; } ;

/* Variables and functions */

__attribute__((used)) static inline int device_enabled(struct loopback_test *t, int dev_idx)
{
	if (!t->mask || (t->mask & (1 << dev_idx)))
		return 1;

	return 0;
}