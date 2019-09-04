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
 char const* __strend (char const*) ; 
 int clcle (char const*,int,char const*,int) ; 

char *strstr(const char *s1, const char *s2)
{
	int l1, l2;

	l2 = __strend(s2) - s2;
	if (!l2)
		return (char *) s1;
	l1 = __strend(s1) - s1;
	while (l1-- >= l2) {
		int cc;

		cc = clcle(s1, l2, s2, l2);
		if (!cc)
			return (char *) s1;
		s1++;
	}
	return NULL;
}