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
 int /*<<< orphan*/  SNIC_ERR (char*,char const*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
snic_ver_enc(const char *s)
{
	int v[4] = {0};
	int  i = 0, x = 0;
	char c;
	const char *p = s;

	/* validate version string */
	if ((strlen(s) > 15) || (strlen(s) < 7))
		goto end;

	while ((c = *p++)) {
		if (c == '.') {
			i++;
			continue;
		}

		if (i > 3 || !isdigit(c))
			goto end;

		v[i] = v[i] * 10 + (c - '0');
	}

	/* validate sub version numbers */
	for (i = 3; i >= 0; i--)
		if (v[i] > 0xff)
			goto end;

	x |= (v[0] << 24) | v[1] << 16 | v[2] << 8 | v[3];

end:
	if (x == 0) {
		SNIC_ERR("Invalid version string [%s].\n", s);

		return -1;
	}

	return x;
}