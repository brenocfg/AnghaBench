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
typedef  int u_char ;

/* Variables and functions */

u_char *
findie(u_char *p, int size, u_char ie, int wanted_set)
{
	int l, codeset, maincodeset;
	u_char *pend = p + size;

	/* skip protocol discriminator, callref and message type */
	p++;
	l = (*p++) & 0xf;
	p += l;
	p++;
	codeset = 0;
	maincodeset = 0;
	/* while there are bytes left... */
	while (p < pend) {
		if ((*p & 0xf0) == 0x90) {
			codeset = *p & 0x07;
			if (!(*p & 0x08))
				maincodeset = codeset;
		}
		if (*p & 0x80)
			p++;
		else {
			if (codeset == wanted_set) {
				if (*p == ie)
				{ /* improved length check (Werner Cornelius) */
					if ((pend - p) < 2)
						return (NULL);
					if (*(p + 1) > (pend - (p + 2)))
						return (NULL);
					return (p);
				}

				if (*p > ie)
					return (NULL);
			}
			p++;
			l = *p++;
			p += l;
			codeset = maincodeset;
		}
	}
	return (NULL);
}