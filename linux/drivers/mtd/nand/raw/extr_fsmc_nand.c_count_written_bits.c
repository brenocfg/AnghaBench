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
 scalar_t__ hweight8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int count_written_bits(u8 *buff, int size, int max_bits)
{
	int k, written_bits = 0;

	for (k = 0; k < size; k++) {
		written_bits += hweight8(~buff[k]);
		if (written_bits > max_bits)
			break;
	}

	return written_bits;
}