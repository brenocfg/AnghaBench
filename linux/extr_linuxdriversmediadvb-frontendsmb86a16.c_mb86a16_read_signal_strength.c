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
struct mb86a16_state {int dummy; } ;
struct dvb_frontend {struct mb86a16_state* demodulator_priv; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  MB86A16_AGCM ; 
 int /*<<< orphan*/  MB86A16_DEBUG ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int mb86a16_read (struct mb86a16_state*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int mb86a16_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	u8 agcm = 0;
	struct mb86a16_state *state = fe->demodulator_priv;

	*strength = 0;
	if (mb86a16_read(state, MB86A16_AGCM, &agcm) != 2) {
		dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		return -EREMOTEIO;
	}

	*strength = ((0xff - agcm) * 100) / 256;
	dprintk(verbose, MB86A16_DEBUG, 1, "Signal strength=[%d %%]", (u8) *strength);
	*strength = (0xffff - 0xff) + agcm;

	return 0;
}