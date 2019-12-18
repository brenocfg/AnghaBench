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
 int /*<<< orphan*/  sscanf (char const*,char*,int*,int*,int*,int*,int*,int*,int*,...) ; 

__attribute__((used)) static inline int str_to_quirk(const char *buf, int *domain, int *bus, int
			       *slot, int *func, int *reg, int *size, int *mask)
{
	int parsed = 0;

	sscanf(buf, " %x:%x:%x.%x-%x:%x:%x %n", domain, bus, slot, func,
	       reg, size, mask, &parsed);
	if (parsed && !buf[parsed])
		return 0;

	/* try again without domain */
	*domain = 0;
	sscanf(buf, " %x:%x.%x-%x:%x:%x %n", bus, slot, func, reg, size,
	       mask, &parsed);
	if (parsed && !buf[parsed])
		return 0;

	return -EINVAL;
}