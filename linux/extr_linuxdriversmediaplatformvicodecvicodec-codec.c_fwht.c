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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */

__attribute__((used)) static void fwht(const u8 *block, s16 *output_block, unsigned int stride,
		 unsigned int input_step, bool intra)
{
	/* we'll need more than 8 bits for the transformed coefficients */
	s32 workspace1[8], workspace2[8];
	const u8 *tmp = block;
	s16 *out = output_block;
	int add = intra ? 256 : 0;
	unsigned int i;

	/* stage 1 */
	stride *= input_step;

	for (i = 0; i < 8; i++, tmp += stride, out += 8) {
		if (input_step == 1) {
			workspace1[0]  = tmp[0] + tmp[1] - add;
			workspace1[1]  = tmp[0] - tmp[1];

			workspace1[2]  = tmp[2] + tmp[3] - add;
			workspace1[3]  = tmp[2] - tmp[3];

			workspace1[4]  = tmp[4] + tmp[5] - add;
			workspace1[5]  = tmp[4] - tmp[5];

			workspace1[6]  = tmp[6] + tmp[7] - add;
			workspace1[7]  = tmp[6] - tmp[7];
		} else {
			workspace1[0]  = tmp[0] + tmp[2] - add;
			workspace1[1]  = tmp[0] - tmp[2];

			workspace1[2]  = tmp[4] + tmp[6] - add;
			workspace1[3]  = tmp[4] - tmp[6];

			workspace1[4]  = tmp[8] + tmp[10] - add;
			workspace1[5]  = tmp[8] - tmp[10];

			workspace1[6]  = tmp[12] + tmp[14] - add;
			workspace1[7]  = tmp[12] - tmp[14];
		}

		/* stage 2 */
		workspace2[0] = workspace1[0] + workspace1[2];
		workspace2[1] = workspace1[0] - workspace1[2];
		workspace2[2] = workspace1[1] - workspace1[3];
		workspace2[3] = workspace1[1] + workspace1[3];

		workspace2[4] = workspace1[4] + workspace1[6];
		workspace2[5] = workspace1[4] - workspace1[6];
		workspace2[6] = workspace1[5] - workspace1[7];
		workspace2[7] = workspace1[5] + workspace1[7];

		/* stage 3 */
		out[0] = workspace2[0] + workspace2[4];
		out[1] = workspace2[0] - workspace2[4];
		out[2] = workspace2[1] - workspace2[5];
		out[3] = workspace2[1] + workspace2[5];
		out[4] = workspace2[2] + workspace2[6];
		out[5] = workspace2[2] - workspace2[6];
		out[6] = workspace2[3] - workspace2[7];
		out[7] = workspace2[3] + workspace2[7];
	}

	out = output_block;

	for (i = 0; i < 8; i++, out++) {
		/* stage 1 */
		workspace1[0]  = out[0] + out[1 * 8];
		workspace1[1]  = out[0] - out[1 * 8];

		workspace1[2]  = out[2 * 8] + out[3 * 8];
		workspace1[3]  = out[2 * 8] - out[3 * 8];

		workspace1[4]  = out[4 * 8] + out[5 * 8];
		workspace1[5]  = out[4 * 8] - out[5 * 8];

		workspace1[6]  = out[6 * 8] + out[7 * 8];
		workspace1[7]  = out[6 * 8] - out[7 * 8];

		/* stage 2 */
		workspace2[0] = workspace1[0] + workspace1[2];
		workspace2[1] = workspace1[0] - workspace1[2];
		workspace2[2] = workspace1[1] - workspace1[3];
		workspace2[3] = workspace1[1] + workspace1[3];

		workspace2[4] = workspace1[4] + workspace1[6];
		workspace2[5] = workspace1[4] - workspace1[6];
		workspace2[6] = workspace1[5] - workspace1[7];
		workspace2[7] = workspace1[5] + workspace1[7];
		/* stage 3 */
		out[0 * 8] = workspace2[0] + workspace2[4];
		out[1 * 8] = workspace2[0] - workspace2[4];
		out[2 * 8] = workspace2[1] - workspace2[5];
		out[3 * 8] = workspace2[1] + workspace2[5];
		out[4 * 8] = workspace2[2] + workspace2[6];
		out[5 * 8] = workspace2[2] - workspace2[6];
		out[6 * 8] = workspace2[3] - workspace2[7];
		out[7 * 8] = workspace2[3] + workspace2[7];
	}
}