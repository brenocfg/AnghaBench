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
struct stv0367_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F367CAB_MIX_NCO_INC_HH ; 
 int /*<<< orphan*/  F367CAB_MIX_NCO_INC_HL ; 
 int /*<<< orphan*/  F367CAB_MIX_NCO_INC_LL ; 
 int stv0367_readbits (struct stv0367_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stv0367cab_get_derot_freq(struct stv0367_state *state, u32 adc_hz)
{
	u32 sampled_if;

	sampled_if = stv0367_readbits(state, F367CAB_MIX_NCO_INC_LL) +
			(stv0367_readbits(state, F367CAB_MIX_NCO_INC_HL) << 8) +
			(stv0367_readbits(state, F367CAB_MIX_NCO_INC_HH) << 16);

	sampled_if /= 256;
	sampled_if *= (adc_hz / 1000);
	sampled_if += 1;
	sampled_if /= 32768;

	return sampled_if;
}