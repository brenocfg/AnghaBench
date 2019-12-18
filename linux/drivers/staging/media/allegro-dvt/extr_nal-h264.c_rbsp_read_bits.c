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

__attribute__((used)) static inline int rbsp_read_bits(struct rbsp *rbsp, int n, unsigned int *value)
{
	int i;
	int bit;
	unsigned int tmp = 0;

	if (n > 8 * sizeof(*value))
		return -EINVAL;

	for (i = n; i > 0; i--) {
		bit = rbsp_read_bit(rbsp);
		if (bit < 0)
			return bit;
		tmp |= bit << (i - 1);
	}

	if (value)
		*value = tmp;

	return 0;
}