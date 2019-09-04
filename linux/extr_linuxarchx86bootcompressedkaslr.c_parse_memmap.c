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
 unsigned long long memparse (char*,char**) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int
parse_memmap(char *p, unsigned long long *start, unsigned long long *size)
{
	char *oldp;

	if (!p)
		return -EINVAL;

	/* We don't care about this option here */
	if (!strncmp(p, "exactmap", 8))
		return -EINVAL;

	oldp = p;
	*size = memparse(p, &p);
	if (p == oldp)
		return -EINVAL;

	switch (*p) {
	case '#':
	case '$':
	case '!':
		*start = memparse(p + 1, &p);
		return 0;
	case '@':
		/* memmap=nn@ss specifies usable region, should be skipped */
		*size = 0;
		/* Fall through */
	default:
		/*
		 * If w/o offset, only size specified, memmap=nn[KMG] has the
		 * same behaviour as mem=nn[KMG]. It limits the max address
		 * system can use. Region above the limit should be avoided.
		 */
		*start = 0;
		return 0;
	}

	return -EINVAL;
}