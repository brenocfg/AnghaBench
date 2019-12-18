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
struct stv {int receive_mode; scalar_t__ fectype; scalar_t__ mod_cod; scalar_t__ regoff; int /*<<< orphan*/  pilots; scalar_t__ nr; } ;

/* Variables and functions */
 scalar_t__ DVBS2_64K ; 
 scalar_t__ FE_16APSK_910 ; 
 scalar_t__ FE_32APSK_910 ; 
 scalar_t__ FE_8PSK_910 ; 
 scalar_t__ FE_QPSK_910 ; 
#define  RCVMODE_DVBS 129 
#define  RCVMODE_DVBS2 128 
 scalar_t__ RSTV0910_P2_ACLC2S216A ; 
 scalar_t__ RSTV0910_P2_ACLC2S232A ; 
 scalar_t__ RSTV0910_P2_ACLC2S28 ; 
 scalar_t__ RSTV0910_P2_ACLC2S2Q ; 
 scalar_t__ RSTV0910_P2_DMDCFGMD ; 
 int /*<<< orphan*/  RSTV0910_TSTTSRS ; 
 int get_optim_cloop (struct stv*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_reg (struct stv*,scalar_t__,int*) ; 
 int /*<<< orphan*/  write_reg (struct stv*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_shared_reg (struct stv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tracking_optimization(struct stv *state)
{
	u8 tmp;

	read_reg(state, RSTV0910_P2_DMDCFGMD + state->regoff, &tmp);
	tmp &= ~0xC0;

	switch (state->receive_mode) {
	case RCVMODE_DVBS:
		tmp |= 0x40;
		break;
	case RCVMODE_DVBS2:
		tmp |= 0x80;
		break;
	default:
		tmp |= 0xC0;
		break;
	}
	write_reg(state, RSTV0910_P2_DMDCFGMD + state->regoff, tmp);

	if (state->receive_mode == RCVMODE_DVBS2) {
		/* Disable Reed-Solomon */
		write_shared_reg(state,
				 RSTV0910_TSTTSRS, state->nr ? 0x02 : 0x01,
				 0x03);

		if (state->fectype == DVBS2_64K) {
			u8 aclc = get_optim_cloop(state, state->mod_cod,
						  state->pilots);

			if (state->mod_cod <= FE_QPSK_910) {
				write_reg(state, RSTV0910_P2_ACLC2S2Q +
					  state->regoff, aclc);
			} else if (state->mod_cod <= FE_8PSK_910) {
				write_reg(state, RSTV0910_P2_ACLC2S2Q +
					  state->regoff, 0x2a);
				write_reg(state, RSTV0910_P2_ACLC2S28 +
					  state->regoff, aclc);
			} else if (state->mod_cod <= FE_16APSK_910) {
				write_reg(state, RSTV0910_P2_ACLC2S2Q +
					  state->regoff, 0x2a);
				write_reg(state, RSTV0910_P2_ACLC2S216A +
					  state->regoff, aclc);
			} else if (state->mod_cod <= FE_32APSK_910) {
				write_reg(state, RSTV0910_P2_ACLC2S2Q +
					  state->regoff, 0x2a);
				write_reg(state, RSTV0910_P2_ACLC2S232A +
					  state->regoff, aclc);
			}
		}
	}
	return 0;
}