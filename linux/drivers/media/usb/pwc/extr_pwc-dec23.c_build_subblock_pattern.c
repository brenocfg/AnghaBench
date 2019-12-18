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
struct pwc_dec23_private {unsigned int** table_subblock; } ;
typedef  int /*<<< orphan*/  initial_values ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int const*,int) ; 

__attribute__((used)) static void build_subblock_pattern(struct pwc_dec23_private *pdec)
{
	static const unsigned int initial_values[12] = {
		-0x526500, -0x221200, 0x221200, 0x526500,
			   -0x3de200, 0x3de200,
		-0x6db480, -0x2d5d00, 0x2d5d00, 0x6db480,
			   -0x12c200, 0x12c200

	};
	static const unsigned int values_derivated[12] = {
		0xa4ca, 0x4424, -0x4424, -0xa4ca,
			0x7bc4, -0x7bc4,
		0xdb69, 0x5aba, -0x5aba, -0xdb69,
			0x2584, -0x2584
	};
	unsigned int temp_values[12];
	int i, j;

	memcpy(temp_values, initial_values, sizeof(initial_values));
	for (i = 0; i < 256; i++) {
		for (j = 0; j < 12; j++) {
			pdec->table_subblock[i][j] = temp_values[j];
			temp_values[j] += values_derivated[j];
		}
	}
}