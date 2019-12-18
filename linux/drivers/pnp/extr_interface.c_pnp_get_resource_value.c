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
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 scalar_t__ simple_strtoull (char*,char**,int /*<<< orphan*/ ) ; 
 char* skip_spaces (char*) ; 

__attribute__((used)) static char *pnp_get_resource_value(char *buf,
				    unsigned long type,
				    resource_size_t *start,
				    resource_size_t *end,
				    unsigned long *flags)
{
	if (start)
		*start = 0;
	if (end)
		*end = 0;
	if (flags)
		*flags = 0;

	/* TBD: allow for disabled resources */

	buf = skip_spaces(buf);
	if (start) {
		*start = simple_strtoull(buf, &buf, 0);
		if (end) {
			buf = skip_spaces(buf);
			if (*buf == '-') {
				buf = skip_spaces(buf + 1);
				*end = simple_strtoull(buf, &buf, 0);
			} else
				*end = *start;
		}
	}

	/* TBD: allow for additional flags, e.g., IORESOURCE_WINDOW */

	return buf;
}