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
typedef  int u16 ;
struct nxt6000_state {int dummy; } ;
struct dvb_frontend {struct nxt6000_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFDM_CHC_SNR ; 
 int nxt6000_readreg (struct nxt6000_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nxt6000_read_snr(struct dvb_frontend* fe, u16* snr)
{
	struct nxt6000_state* state = fe->demodulator_priv;

	*snr = nxt6000_readreg( state, OFDM_CHC_SNR) / 8;

	return 0;
}