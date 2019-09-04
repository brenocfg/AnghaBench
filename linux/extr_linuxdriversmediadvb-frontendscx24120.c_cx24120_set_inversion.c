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
struct TYPE_4__ {int inversion_val; int inversion; } ;
struct cx24120_state {TYPE_2__ dnxt; TYPE_1__* i2c; } ;
typedef  enum fe_spectral_inversion { ____Placeholder_fe_spectral_inversion } fe_spectral_inversion ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INVERSION_AUTO 130 
#define  INVERSION_OFF 129 
#define  INVERSION_ON 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int cx24120_set_inversion(struct cx24120_state *state,
				 enum fe_spectral_inversion inversion)
{
	dev_dbg(&state->i2c->dev, "(%d)\n", inversion);

	switch (inversion) {
	case INVERSION_OFF:
		state->dnxt.inversion_val = 0x00;
		break;
	case INVERSION_ON:
		state->dnxt.inversion_val = 0x04;
		break;
	case INVERSION_AUTO:
		state->dnxt.inversion_val = 0x0c;
		break;
	default:
		return -EINVAL;
	}

	state->dnxt.inversion = inversion;

	return 0;
}