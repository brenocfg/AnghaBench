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

__attribute__((used)) static int jornada720_ts_average(int coords[4])
{
	int coord, high_bits = coords[3];

	coord  = coords[0] | ((high_bits & 0x03) << 8);
	coord += coords[1] | ((high_bits & 0x0c) << 6);
	coord += coords[2] | ((high_bits & 0x30) << 4);

	return coord / 3;
}