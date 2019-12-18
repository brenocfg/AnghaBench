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
struct v4l2_ctrl_mpeg2_quantization {int /*<<< orphan*/ * chroma_non_intra_quantiser_matrix; int /*<<< orphan*/ * chroma_intra_quantiser_matrix; int /*<<< orphan*/ * non_intra_quantiser_matrix; int /*<<< orphan*/ * intra_quantiser_matrix; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* zigzag ; 

void hantro_mpeg2_dec_copy_qtable(u8 *qtable,
	const struct v4l2_ctrl_mpeg2_quantization *ctrl)
{
	int i, n;

	if (!qtable || !ctrl)
		return;

	for (i = 0; i < ARRAY_SIZE(zigzag); i++) {
		n = zigzag[i];
		qtable[n + 0] = ctrl->intra_quantiser_matrix[i];
		qtable[n + 64] = ctrl->non_intra_quantiser_matrix[i];
		qtable[n + 128] = ctrl->chroma_intra_quantiser_matrix[i];
		qtable[n + 192] = ctrl->chroma_non_intra_quantiser_matrix[i];
	}
}