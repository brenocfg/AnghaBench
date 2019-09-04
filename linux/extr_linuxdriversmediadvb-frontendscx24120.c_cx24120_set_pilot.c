#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ delsys; void* pilot_val; } ;
struct cx24120_state {TYPE_2__ dnxt; TYPE_1__* i2c; } ;
typedef  enum fe_pilot { ____Placeholder_fe_pilot } fe_pilot ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* CX24120_PILOT_AUTO ; 
 void* CX24120_PILOT_OFF ; 
 void* CX24120_PILOT_ON ; 
#define  PILOT_AUTO 130 
#define  PILOT_OFF 129 
#define  PILOT_ON 128 
 scalar_t__ SYS_DVBS2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int cx24120_set_pilot(struct cx24120_state *state, enum fe_pilot pilot)
{
	dev_dbg(&state->i2c->dev, "(%d)\n", pilot);

	/* Pilot only valid in DVBS2 */
	if (state->dnxt.delsys != SYS_DVBS2) {
		state->dnxt.pilot_val = CX24120_PILOT_OFF;
		return 0;
	}

	switch (pilot) {
	case PILOT_OFF:
		state->dnxt.pilot_val = CX24120_PILOT_OFF;
		break;
	case PILOT_ON:
		state->dnxt.pilot_val = CX24120_PILOT_ON;
		break;
	case PILOT_AUTO:
	default:
		state->dnxt.pilot_val = CX24120_PILOT_AUTO;
	}

	return 0;
}