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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct dc_context {int dummy; } ;
struct color_matrices_reg {scalar_t__ csc_c11_c12; scalar_t__ csc_c33_c34; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SET_2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  csc_c11 ; 
 int /*<<< orphan*/  csc_c12 ; 

void cm_helper_program_color_matrices(
		struct dc_context *ctx,
		const uint16_t *regval,
		const struct color_matrices_reg *reg)
{
	uint32_t cur_csc_reg;
	unsigned int i = 0;

	for (cur_csc_reg = reg->csc_c11_c12;
			cur_csc_reg <= reg->csc_c33_c34;
			cur_csc_reg++) {

		const uint16_t *regval0 = &(regval[2 * i]);
		const uint16_t *regval1 = &(regval[(2 * i) + 1]);

		REG_SET_2(cur_csc_reg, 0,
				csc_c11, *regval0,
				csc_c12, *regval1);

		i++;
	}

}