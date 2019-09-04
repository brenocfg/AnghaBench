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
typedef  int s16 ;

/* Variables and functions */

__attribute__((used)) static void ifwht(const s16 *block, s16 *output_block, int intra)
{
	/*
	 * we'll need more than 8 bits for the transformed coefficients
	 * use native unit of cpu
	 */
	int workspace1[8], workspace2[8];
	int inter = intra ? 0 : 1;
	const s16 *tmp = block;
	s16 *out = output_block;
	int i;

	for (i = 0; i < 8; i++, tmp += 8, out += 8) {
		/* stage 1 */
		workspace1[0]  = tmp[0] + tmp[1];
		workspace1[1]  = tmp[0] - tmp[1];

		workspace1[2]  = tmp[2] + tmp[3];
		workspace1[3]  = tmp[2] - tmp[3];

		workspace1[4]  = tmp[4] + tmp[5];
		workspace1[5]  = tmp[4] - tmp[5];

		workspace1[6]  = tmp[6] + tmp[7];
		workspace1[7]  = tmp[6] - tmp[7];

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
		if (inter) {
			int d;

			out[0 * 8] = workspace2[0] + workspace2[4];
			out[1 * 8] = workspace2[0] - workspace2[4];
			out[2 * 8] = workspace2[1] - workspace2[5];
			out[3 * 8] = workspace2[1] + workspace2[5];
			out[4 * 8] = workspace2[2] + workspace2[6];
			out[5 * 8] = workspace2[2] - workspace2[6];
			out[6 * 8] = workspace2[3] - workspace2[7];
			out[7 * 8] = workspace2[3] + workspace2[7];

			for (d = 0; d < 8; d++)
				out[8 * d] >>= 6;
		} else {
			int d;

			out[0 * 8] = workspace2[0] + workspace2[4];
			out[1 * 8] = workspace2[0] - workspace2[4];
			out[2 * 8] = workspace2[1] - workspace2[5];
			out[3 * 8] = workspace2[1] + workspace2[5];
			out[4 * 8] = workspace2[2] + workspace2[6];
			out[5 * 8] = workspace2[2] - workspace2[6];
			out[6 * 8] = workspace2[3] - workspace2[7];
			out[7 * 8] = workspace2[3] + workspace2[7];

			for (d = 0; d < 8; d++) {
				out[8 * d] >>= 6;
				out[8 * d] += 128;
			}
		}
	}
}