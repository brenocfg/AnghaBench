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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */

__attribute__((used)) static void _dump_field(const char *hdr, u64 n, const char *func, int line)
{
#if defined(DEBUG)
	char s[16];
	const char *const in = (const char *)&n;
	unsigned int i;

	for (i = 0; i < 8; i++)
		s[i] = (in[i] <= 126 && in[i] >= 32) ? in[i] : '.';
	s[i] = 0;

	pr_devel("%s:%d: %s%016llx : %s\n", func, line, hdr, n, s);
#endif
}