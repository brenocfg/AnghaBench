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
 unsigned long INT_MAX ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 unsigned long simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bytes_str_to_int(const char *str)
{
	char *endp;
	unsigned long result;

	result = simple_strtoul(str, &endp, 0);
	if (str == endp || result >= INT_MAX) {
		pr_err("UBI error: incorrect bytes count: \"%s\"\n", str);
		return -EINVAL;
	}

	switch (*endp) {
	case 'G':
		result *= 1024;
		/* fall through */
	case 'M':
		result *= 1024;
		/* fall through */
	case 'K':
		result *= 1024;
		if (endp[1] == 'i' && endp[2] == 'B')
			endp += 2;
	case '\0':
		break;
	default:
		pr_err("UBI error: incorrect bytes count: \"%s\"\n", str);
		return -EINVAL;
	}

	return result;
}