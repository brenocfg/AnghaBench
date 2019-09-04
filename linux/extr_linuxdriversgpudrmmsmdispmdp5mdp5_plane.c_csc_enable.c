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
typedef  int uint32_t ;
struct mdp5_kms {int dummy; } ;
struct csc_cfg {scalar_t__ type; int* matrix; int* pre_clamp; int* post_clamp; int /*<<< orphan*/ * post_bias; int /*<<< orphan*/ * pre_bias; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ CSC_RGB2YUV ; 
 scalar_t__ CSC_YUV2RGB ; 
 scalar_t__ CSC_YUV2YUV ; 
 int /*<<< orphan*/  DATA_FORMAT_YUV ; 
 int MDP5_PIPE_CSC_1_MATRIX_COEFF_0_COEFF_11 (int) ; 
 int MDP5_PIPE_CSC_1_MATRIX_COEFF_0_COEFF_12 (int) ; 
 int MDP5_PIPE_CSC_1_MATRIX_COEFF_1_COEFF_13 (int) ; 
 int MDP5_PIPE_CSC_1_MATRIX_COEFF_1_COEFF_21 (int) ; 
 int MDP5_PIPE_CSC_1_MATRIX_COEFF_2_COEFF_22 (int) ; 
 int MDP5_PIPE_CSC_1_MATRIX_COEFF_2_COEFF_23 (int) ; 
 int MDP5_PIPE_CSC_1_MATRIX_COEFF_3_COEFF_31 (int) ; 
 int MDP5_PIPE_CSC_1_MATRIX_COEFF_3_COEFF_32 (int) ; 
 int MDP5_PIPE_CSC_1_MATRIX_COEFF_4_COEFF_33 (int) ; 
 int MDP5_PIPE_CSC_1_POST_BIAS_REG_VALUE (int /*<<< orphan*/ ) ; 
 int MDP5_PIPE_CSC_1_POST_CLAMP_REG_HIGH (int) ; 
 int MDP5_PIPE_CSC_1_POST_CLAMP_REG_LOW (int) ; 
 int MDP5_PIPE_CSC_1_PRE_BIAS_REG_VALUE (int /*<<< orphan*/ ) ; 
 int MDP5_PIPE_CSC_1_PRE_CLAMP_REG_HIGH (int) ; 
 int MDP5_PIPE_CSC_1_PRE_CLAMP_REG_LOW (int) ; 
 int MDP5_PIPE_OP_MODE_CSC_1_EN ; 
 int MDP5_PIPE_OP_MODE_CSC_DST_DATA_FORMAT (int /*<<< orphan*/ ) ; 
 int MDP5_PIPE_OP_MODE_CSC_SRC_DATA_FORMAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_0 (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_1 (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_2 (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_3 (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_4 (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_CSC_1_POST_BIAS (int,int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_CSC_1_POST_CLAMP (int,int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_CSC_1_PRE_BIAS (int,int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_CSC_1_PRE_CLAMP (int,int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_OP_MODE (int) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void csc_enable(struct mdp5_kms *mdp5_kms, enum mdp5_pipe pipe,
		struct csc_cfg *csc)
{
	uint32_t  i, mode = 0; /* RGB, no CSC */
	uint32_t *matrix;

	if (unlikely(!csc))
		return;

	if ((csc->type == CSC_YUV2RGB) || (CSC_YUV2YUV == csc->type))
		mode |= MDP5_PIPE_OP_MODE_CSC_SRC_DATA_FORMAT(DATA_FORMAT_YUV);
	if ((csc->type == CSC_RGB2YUV) || (CSC_YUV2YUV == csc->type))
		mode |= MDP5_PIPE_OP_MODE_CSC_DST_DATA_FORMAT(DATA_FORMAT_YUV);
	mode |= MDP5_PIPE_OP_MODE_CSC_1_EN;
	mdp5_write(mdp5_kms, REG_MDP5_PIPE_OP_MODE(pipe), mode);

	matrix = csc->matrix;
	mdp5_write(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_0(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_0_COEFF_11(matrix[0]) |
			MDP5_PIPE_CSC_1_MATRIX_COEFF_0_COEFF_12(matrix[1]));
	mdp5_write(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_1(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_1_COEFF_13(matrix[2]) |
			MDP5_PIPE_CSC_1_MATRIX_COEFF_1_COEFF_21(matrix[3]));
	mdp5_write(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_2(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_2_COEFF_22(matrix[4]) |
			MDP5_PIPE_CSC_1_MATRIX_COEFF_2_COEFF_23(matrix[5]));
	mdp5_write(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_3(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_3_COEFF_31(matrix[6]) |
			MDP5_PIPE_CSC_1_MATRIX_COEFF_3_COEFF_32(matrix[7]));
	mdp5_write(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_4(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_4_COEFF_33(matrix[8]));

	for (i = 0; i < ARRAY_SIZE(csc->pre_bias); i++) {
		uint32_t *pre_clamp = csc->pre_clamp;
		uint32_t *post_clamp = csc->post_clamp;

		mdp5_write(mdp5_kms, REG_MDP5_PIPE_CSC_1_PRE_CLAMP(pipe, i),
			MDP5_PIPE_CSC_1_PRE_CLAMP_REG_HIGH(pre_clamp[2*i+1]) |
			MDP5_PIPE_CSC_1_PRE_CLAMP_REG_LOW(pre_clamp[2*i]));

		mdp5_write(mdp5_kms, REG_MDP5_PIPE_CSC_1_POST_CLAMP(pipe, i),
			MDP5_PIPE_CSC_1_POST_CLAMP_REG_HIGH(post_clamp[2*i+1]) |
			MDP5_PIPE_CSC_1_POST_CLAMP_REG_LOW(post_clamp[2*i]));

		mdp5_write(mdp5_kms, REG_MDP5_PIPE_CSC_1_PRE_BIAS(pipe, i),
			MDP5_PIPE_CSC_1_PRE_BIAS_REG_VALUE(csc->pre_bias[i]));

		mdp5_write(mdp5_kms, REG_MDP5_PIPE_CSC_1_POST_BIAS(pipe, i),
			MDP5_PIPE_CSC_1_POST_BIAS_REG_VALUE(csc->post_bias[i]));
	}
}