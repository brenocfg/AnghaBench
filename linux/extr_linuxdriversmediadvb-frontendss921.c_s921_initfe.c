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
struct s921_state {int dummy; } ;
struct dvb_frontend {struct s921_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  s921_init ; 
 int s921_writeregdata (struct s921_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s921_initfe(struct dvb_frontend *fe)
{
	struct s921_state *state = fe->demodulator_priv;
	int rc;

	dprintk("\n");

	rc = s921_writeregdata(state, s921_init);
	if (rc < 0)
		return rc;

	return 0;
}