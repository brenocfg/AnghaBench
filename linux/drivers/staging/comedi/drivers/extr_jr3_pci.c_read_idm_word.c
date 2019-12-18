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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int hex_to_bin (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  isxdigit (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int read_idm_word(const u8 *data, size_t size, int *pos,
			 unsigned int *val)
{
	int result = 0;
	int value;

	if (pos && val) {
		/* Skip over non hex */
		for (; *pos < size && !isxdigit(data[*pos]); (*pos)++)
			;
		/* Collect value */
		*val = 0;
		for (; *pos < size; (*pos)++) {
			value = hex_to_bin(data[*pos]);
			if (value >= 0) {
				result = 1;
				*val = (*val << 4) + value;
			} else {
				break;
			}
		}
	}
	return result;
}