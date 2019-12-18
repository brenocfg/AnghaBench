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
typedef  scalar_t__ u32 ;
struct host1x_firewall {scalar_t__ words; int /*<<< orphan*/  offset; scalar_t__ reg; scalar_t__ count; } ;

/* Variables and functions */
 int EINVAL ; 
 int check_register (struct host1x_firewall*,scalar_t__) ; 

__attribute__((used)) static int check_incr(struct host1x_firewall *fw)
{
	u32 count = fw->count;
	u32 reg = fw->reg;
	int ret;

	while (count) {
		if (fw->words == 0)
			return -EINVAL;

		ret = check_register(fw, reg);
		if (ret < 0)
			return ret;

		reg++;
		fw->words--;
		fw->offset++;
		count--;
	}

	return 0;
}