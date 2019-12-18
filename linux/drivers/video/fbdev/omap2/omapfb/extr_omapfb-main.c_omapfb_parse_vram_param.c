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
 int /*<<< orphan*/  WARN_ONCE (unsigned long,char*) ; 
 unsigned long memparse (char*,char**) ; 
 void* simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static int omapfb_parse_vram_param(const char *param, int max_entries,
		unsigned long *sizes, unsigned long *paddrs)
{
	unsigned int fbnum;
	unsigned long size;
	unsigned long paddr = 0;
	char *p, *start;

	start = (char *)param;

	while (1) {
		p = start;

		fbnum = simple_strtoul(p, &p, 10);

		if (p == start)
			return -EINVAL;

		if (*p != ':')
			return -EINVAL;

		if (fbnum >= max_entries)
			return -EINVAL;

		size = memparse(p + 1, &p);

		if (!size)
			return -EINVAL;

		paddr = 0;

		if (*p == '@') {
			paddr = simple_strtoul(p + 1, &p, 16);

			if (!paddr)
				return -EINVAL;

		}

		WARN_ONCE(paddr,
			"reserving memory at predefined address not supported\n");

		paddrs[fbnum] = paddr;
		sizes[fbnum] = size;

		if (*p == 0)
			break;

		if (*p != ',')
			return -EINVAL;

		++p;

		start = p;
	}

	return 0;
}