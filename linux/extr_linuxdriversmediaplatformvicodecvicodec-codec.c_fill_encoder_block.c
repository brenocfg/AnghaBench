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
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */

__attribute__((used)) static void fill_encoder_block(const u8 *input, s16 *dst,
			       unsigned int stride, unsigned int input_step)
{
	int i, j;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++, input += input_step)
			*dst++ = *input;
		input += (stride - 8) * input_step;
	}
}