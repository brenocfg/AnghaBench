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
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  isxdigit (char) ; 

__attribute__((used)) static int strval_len(char *b)
{
	char *s = b;

	if ((*s == '0') && ((*(s+1) == 'x') || (*(s+1) == 'X'))) {
		s += 2;
		for (; *s && (*s != ' ') && (*s != '\n'); s++) {
			if (!isxdigit(*s))
				return 0;
		}
	} else {
		if (*s == '-')
			s++;
		for (; *s && (*s != ' ') && (*s != '\n'); s++) {
			if (!isdigit(*s))
				return 0;
		}
	}
	return (int) (s-b);
}