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
typedef  char u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpus (int /*<<< orphan*/ *) ; 

void ide_fixstring(u8 *s, const int bytecount, const int byteswap)
{
	u8 *p, *end = &s[bytecount & ~1]; /* bytecount must be even */

	if (byteswap) {
		/* convert from big-endian to host byte order */
		for (p = s ; p != end ; p += 2)
			be16_to_cpus((u16 *) p);
	}

	/* strip leading blanks */
	p = s;
	while (s != end && *s == ' ')
		++s;
	/* compress internal blanks and strip trailing blanks */
	while (s != end && *s) {
		if (*s++ != ' ' || (s != end && *s && *s != ' '))
			*p++ = *(s-1);
	}
	/* wipe out trailing garbage */
	while (p != end)
		*p++ = '\0';
}