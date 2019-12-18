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
 int rbsp_read_uev (struct rbsp*,unsigned int*) ; 

__attribute__((used)) static int rbsp_read_sev(struct rbsp *rbsp, int *value)
{
	int ret;
	unsigned int tmp;

	ret = rbsp_read_uev(rbsp, &tmp);
	if (ret)
		return ret;

	if (value) {
		if (tmp & 1)
			*value = (tmp + 1) / 2;
		else
			*value = -(tmp / 2);
	}

	return 0;
}