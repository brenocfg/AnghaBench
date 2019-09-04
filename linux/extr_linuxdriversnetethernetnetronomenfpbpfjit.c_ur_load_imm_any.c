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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 scalar_t__ FIELD_FIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UR_REG_IMM_MAX ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static swreg ur_load_imm_any(struct nfp_prog *nfp_prog, u32 imm, swreg tmp_reg)
{
	if (FIELD_FIT(UR_REG_IMM_MAX, imm))
		return reg_imm(imm);

	wrp_immed(nfp_prog, tmp_reg, imm);
	return tmp_reg;
}