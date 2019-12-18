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
struct rbsp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int rbsp_read_bit (struct rbsp*) ; 

__attribute__((used)) static inline int rbsp_read_bits(struct rbsp *rbsp, int num, int *val)
{
	int i, ret;
	int tmp = 0;

	if (num > 32)
		return -EINVAL;

	for (i = 0; i < num; i++) {
		ret = rbsp_read_bit(rbsp);
		if (ret < 0)
			return ret;
		tmp |= ret << (num - i - 1);
	}

	if (val)
		*val = tmp;

	return 0;
}