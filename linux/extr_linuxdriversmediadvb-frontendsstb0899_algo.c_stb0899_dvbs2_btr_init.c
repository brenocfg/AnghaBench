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
typedef  int u32 ;
struct stb0899_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTR_CNTRL ; 
 int /*<<< orphan*/  BTR_ERR_ENA ; 
 int /*<<< orphan*/  INTRP_PHS_SENSE ; 
 int /*<<< orphan*/  STB0899_BASE_BTR_CNTRL ; 
 int /*<<< orphan*/  STB0899_BASE_BTR_FREQ_INIT ; 
 int /*<<< orphan*/  STB0899_BASE_BTR_PHS_INIT ; 
 int /*<<< orphan*/  STB0899_OFF0_BTR_CNTRL ; 
 int /*<<< orphan*/  STB0899_OFF0_BTR_FREQ_INIT ; 
 int /*<<< orphan*/  STB0899_OFF0_BTR_PHS_INIT ; 
 int STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stb0899_write_s2reg (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stb0899_dvbs2_btr_init(struct stb0899_state *state)
{
	u32 reg;

	/* set enable BTR loopback	*/
	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, BTR_CNTRL);
	STB0899_SETFIELD_VAL(INTRP_PHS_SENSE, reg, 1);
	STB0899_SETFIELD_VAL(BTR_ERR_ENA, reg, 1);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_CNTRL, STB0899_OFF0_BTR_CNTRL, reg);

	/* fix btr freq accum at 0	*/
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_FREQ_INIT, STB0899_OFF0_BTR_FREQ_INIT, 0x10000000);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_FREQ_INIT, STB0899_OFF0_BTR_FREQ_INIT, 0x00000000);

	/* fix btr freq accum at 0	*/
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_PHS_INIT, STB0899_OFF0_BTR_PHS_INIT, 0x10000000);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_PHS_INIT, STB0899_OFF0_BTR_PHS_INIT, 0x00000000);
}