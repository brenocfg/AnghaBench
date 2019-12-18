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
struct nxt200x_state {int initialised; int demod_chip; } ;
struct dvb_frontend {struct nxt200x_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NXT2002 129 
#define  NXT2004 128 
 int nxt2002_init (struct dvb_frontend*) ; 
 int nxt2004_init (struct dvb_frontend*) ; 

__attribute__((used)) static int nxt200x_init(struct dvb_frontend* fe)
{
	struct nxt200x_state* state = fe->demodulator_priv;
	int ret = 0;

	if (!state->initialised) {
		switch (state->demod_chip) {
			case NXT2002:
				ret = nxt2002_init(fe);
				break;
			case NXT2004:
				ret = nxt2004_init(fe);
				break;
			default:
				return -EINVAL;
				break;
		}
		state->initialised = 1;
	}
	return ret;
}