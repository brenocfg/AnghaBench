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
typedef  int /*<<< orphan*/  value ;
struct rbsp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int rbsp_write_bit (struct rbsp*,unsigned int) ; 

__attribute__((used)) static int rbsp_write_bits(struct rbsp *rbsp, int n, unsigned int value)
{
	int ret;

	if (n > 8 * sizeof(value))
		return -EINVAL;

	while (n--) {
		ret = rbsp_write_bit(rbsp, (value >> n) & 1);
		if (ret)
			return ret;
	}

	return 0;
}