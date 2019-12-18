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

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ustrtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_num(size_t *num, const char *token)
{
	char *endp;
	size_t n;

	n = (size_t) ustrtoul(token, &endp, 0);
	if (*endp)
		return -EINVAL;

	*num = n;
	return 0;
}