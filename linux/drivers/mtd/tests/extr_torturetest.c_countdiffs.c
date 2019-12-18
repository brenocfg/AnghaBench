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

__attribute__((used)) static int countdiffs(unsigned char *buf, unsigned char *check_buf,
		      unsigned offset, unsigned len, unsigned *bytesp,
		      unsigned *bitsp)
{
	unsigned i, bit;
	int first = -1;

	for (i = offset; i < offset + len; i++)
		if (buf[i] != check_buf[i]) {
			first = i;
			break;
		}

	while (i < offset + len) {
		if (buf[i] != check_buf[i]) {
			(*bytesp)++;
			bit = 1;
			while (bit < 256) {
				if ((buf[i] & bit) != (check_buf[i] & bit))
					(*bitsp)++;
				bit <<= 1;
			}
		}
		i++;
	}

	return first;
}