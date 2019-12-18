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
typedef  scalar_t__ u32 ;
struct mt2063_state {int /*<<< orphan*/  init; } ;
struct dvb_frontend {struct mt2063_state* tuner_priv; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ TUNER_STATUS_LOCKED ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int mt2063_lockStatus (struct mt2063_state*) ; 

__attribute__((used)) static int mt2063_get_status(struct dvb_frontend *fe, u32 *tuner_status)
{
	struct mt2063_state *state = fe->tuner_priv;
	int status;

	dprintk(2, "\n");

	if (!state->init)
		return -ENODEV;

	*tuner_status = 0;
	status = mt2063_lockStatus(state);
	if (status < 0)
		return status;
	if (status)
		*tuner_status = TUNER_STATUS_LOCKED;

	dprintk(1, "Tuner status: %d", *tuner_status);

	return 0;
}