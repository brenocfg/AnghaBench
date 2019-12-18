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
typedef  int u8 ;
typedef  int u16 ;
struct stv {scalar_t__* vth; scalar_t__ regoff; } ;
struct slookup {int member_0; int member_1; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct slookup const*) ; 
 scalar_t__ RSTV0910_P2_NNOSDATAT1 ; 
 scalar_t__ RSTV0910_P2_VTH12 ; 
 int read_regs (struct stv*,scalar_t__,int*,int) ; 
 scalar_t__ table_lookup (struct slookup const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_reg (struct stv*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int set_vth(struct stv *state)
{
	static const struct slookup vthlookup_table[] = {
		{250,	8780}, /* C/N= 1.5dB */
		{100,	7405}, /* C/N= 4.5dB */
		{40,	6330}, /* C/N= 6.5dB */
		{12,	5224}, /* C/N= 8.5dB */
		{5,	4236}  /* C/N=10.5dB */
	};

	int i;
	u8 tmp[2];
	int status = read_regs(state,
			       RSTV0910_P2_NNOSDATAT1 + state->regoff,
			       tmp, 2);
	u16 reg_value = (tmp[0] << 8) | tmp[1];
	s32 vth = table_lookup(vthlookup_table, ARRAY_SIZE(vthlookup_table),
			      reg_value);

	for (i = 0; i < 6; i += 1)
		if (state->vth[i] > vth)
			state->vth[i] = vth;

	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 0, state->vth[0]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 1, state->vth[1]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 2, state->vth[2]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 3, state->vth[3]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 4, state->vth[4]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 5, state->vth[5]);
	return status;
}