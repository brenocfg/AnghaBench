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

__attribute__((used)) static int append_str(char *buf, char **curp, int *lenp, const char *s)
{
	char *p = *curp;
	int len = *lenp;
	int result = 0; /* success */
	char c;

	/* add a comma, if first in the buffer */
	if (p != buf) {
		if (len == 0) {
			result = 1; /* out of room */
			goto done;
		}
		*p++ = ',';
		len--;
	}

	/* copy the string */
	while ((c = *s++) != 0) {
		if (len == 0) {
			result = 1; /* out of room */
			goto done;
		}
		*p++ = c;
		len--;
	}

done:
	/* write return values */
	*curp = p;
	*lenp = len;

	return result;
}