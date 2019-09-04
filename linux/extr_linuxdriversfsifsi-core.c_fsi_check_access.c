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
typedef  int uint32_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int fsi_check_access(uint32_t addr, size_t size)
{
	if (size == 4) {
		if (addr & 0x3)
			return -EINVAL;
	} else if (size == 2) {
		if (addr & 0x1)
			return -EINVAL;
	} else if (size != 1)
		return -EINVAL;

	return 0;
}