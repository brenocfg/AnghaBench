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
typedef  enum fe_guard_interval { ____Placeholder_fe_guard_interval } fe_guard_interval ;

/* Variables and functions */
 int EINVAL ; 
#define  GUARD_INTERVAL_1_16 132 
#define  GUARD_INTERVAL_1_32 131 
#define  GUARD_INTERVAL_1_4 130 
#define  GUARD_INTERVAL_1_8 129 
#define  GUARD_INTERVAL_AUTO 128 
 int /*<<< orphan*/  OFDM_COR_MODEGUARD ; 
 int nxt6000_readreg (struct nxt6000_state*,int /*<<< orphan*/ ) ; 
 int nxt6000_writereg (struct nxt6000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nxt6000_set_guard_interval(struct nxt6000_state *state,
				      enum fe_guard_interval guard_interval)
{
	switch (guard_interval) {

	case GUARD_INTERVAL_1_32:
		return nxt6000_writereg(state, OFDM_COR_MODEGUARD, 0x00 | (nxt6000_readreg(state, OFDM_COR_MODEGUARD) & ~0x03));

	case GUARD_INTERVAL_1_16:
		return nxt6000_writereg(state, OFDM_COR_MODEGUARD, 0x01 | (nxt6000_readreg(state, OFDM_COR_MODEGUARD) & ~0x03));

	case GUARD_INTERVAL_AUTO:
	case GUARD_INTERVAL_1_8:
		return nxt6000_writereg(state, OFDM_COR_MODEGUARD, 0x02 | (nxt6000_readreg(state, OFDM_COR_MODEGUARD) & ~0x03));

	case GUARD_INTERVAL_1_4:
		return nxt6000_writereg(state, OFDM_COR_MODEGUARD, 0x03 | (nxt6000_readreg(state, OFDM_COR_MODEGUARD) & ~0x03));

	default:
		return -EINVAL;
	}
}