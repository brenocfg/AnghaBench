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
struct stm32_dfsdm_str2field {int val; scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static int stm32_dfsdm_str2val(const char *str,
			       const struct stm32_dfsdm_str2field *list)
{
	const struct stm32_dfsdm_str2field *p = list;

	for (p = list; p && p->name; p++)
		if (!strcmp(p->name, str))
			return p->val;

	return -EINVAL;
}