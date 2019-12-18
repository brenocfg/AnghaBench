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
struct dvb_frontend {struct nxt6000_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  nxt6000_reset (struct nxt6000_state*) ; 
 int /*<<< orphan*/  nxt6000_setup (struct dvb_frontend*) ; 

__attribute__((used)) static int nxt6000_init(struct dvb_frontend* fe)
{
	struct nxt6000_state* state = fe->demodulator_priv;

	nxt6000_reset(state);
	nxt6000_setup(fe);

	return 0;
}