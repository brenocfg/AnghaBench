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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int nr64_ipp (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int __niu_wait_bits_clear_ipp(struct niu *np, unsigned long reg,
				     u64 bits, int limit, int delay)
{
	while (--limit >= 0) {
		u64 val = nr64_ipp(reg);

		if (!(val & bits))
			break;
		udelay(delay);
	}
	if (limit < 0)
		return -ENODEV;
	return 0;
}