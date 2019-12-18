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
typedef  int uint64_t ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtou64 (char*,int /*<<< orphan*/ ,int*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int parse_num64(uint64_t *num64, char *token)
{
	size_t len;
	int shift = 0;
	int ret;

	len = strlen(token);
	/* By dwmw2 editorial decree, "ki", "Mi" or "Gi" are to be used. */
	if (len > 2) {
		if (token[len - 1] == 'i') {
			switch (token[len - 2]) {
			case 'G':
				shift += 10;
				/* fall through */
			case 'M':
				shift += 10;
				/* fall through */
			case 'k':
				shift += 10;
				token[len - 2] = 0;
				break;
			default:
				return -EINVAL;
			}
		}
	}

	ret = kstrtou64(token, 0, num64);
	*num64 <<= shift;

	return ret;
}