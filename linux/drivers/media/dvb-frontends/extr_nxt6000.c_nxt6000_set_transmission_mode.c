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
struct nxt6000_state {int dummy; } ;
typedef  enum fe_transmit_mode { ____Placeholder_fe_transmit_mode } fe_transmit_mode ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EN_DMD_RACQ ; 
 int /*<<< orphan*/  OFDM_COR_MODEGUARD ; 
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_8K 129 
#define  TRANSMISSION_MODE_AUTO 128 
 int nxt6000_readreg (struct nxt6000_state*,int /*<<< orphan*/ ) ; 
 int nxt6000_writereg (struct nxt6000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nxt6000_set_transmission_mode(struct nxt6000_state *state,
			      enum fe_transmit_mode transmission_mode)
{
	int result;

	switch (transmission_mode) {

	case TRANSMISSION_MODE_2K:
		if ((result = nxt6000_writereg(state, EN_DMD_RACQ, 0x00 | (nxt6000_readreg(state, EN_DMD_RACQ) & ~0x03))) < 0)
			return result;

		return nxt6000_writereg(state, OFDM_COR_MODEGUARD, (0x00 << 2) | (nxt6000_readreg(state, OFDM_COR_MODEGUARD) & ~0x04));

	case TRANSMISSION_MODE_8K:
	case TRANSMISSION_MODE_AUTO:
		if ((result = nxt6000_writereg(state, EN_DMD_RACQ, 0x02 | (nxt6000_readreg(state, EN_DMD_RACQ) & ~0x03))) < 0)
			return result;

		return nxt6000_writereg(state, OFDM_COR_MODEGUARD, (0x01 << 2) | (nxt6000_readreg(state, OFDM_COR_MODEGUARD) & ~0x04));

	default:
		return -EINVAL;

	}
}