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
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 

int iio_str_to_fixpoint(const char *str, int fract_mult,
	int *integer, int *fract)
{
	int i = 0, f = 0;
	bool integer_part = true, negative = false;

	if (fract_mult == 0) {
		*fract = 0;

		return kstrtoint(str, 0, integer);
	}

	if (str[0] == '-') {
		negative = true;
		str++;
	} else if (str[0] == '+') {
		str++;
	}

	while (*str) {
		if ('0' <= *str && *str <= '9') {
			if (integer_part) {
				i = i * 10 + *str - '0';
			} else {
				f += fract_mult * (*str - '0');
				fract_mult /= 10;
			}
		} else if (*str == '\n') {
			if (*(str + 1) == '\0')
				break;
			else
				return -EINVAL;
		} else if (*str == '.' && integer_part) {
			integer_part = false;
		} else {
			return -EINVAL;
		}
		str++;
	}

	if (negative) {
		if (i)
			i = -i;
		else
			f = -f;
	}

	*integer = i;
	*fract = f;

	return 0;
}