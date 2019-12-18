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
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int iwpm_validate_nlmsg_attr(struct nlattr *nltb[],
					   int nla_count)
{
	int i;
	for (i = 1; i < nla_count; i++) {
		if (!nltb[i])
			return -EINVAL;
	}
	return 0;
}