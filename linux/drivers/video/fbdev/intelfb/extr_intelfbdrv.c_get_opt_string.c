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
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* OPT_STRVAL (char const*,char const*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static __inline__ char * get_opt_string(const char *this_opt, const char *name)
{
	const char *p;
	int i;
	char *ret;

	p = OPT_STRVAL(this_opt, name);
	i = 0;
	while (p[i] && p[i] != ' ' && p[i] != ',')
		i++;
	ret = kmalloc(i + 1, GFP_KERNEL);
	if (ret) {
		strncpy(ret, p, i);
		ret[i] = '\0';
	}
	return ret;
}