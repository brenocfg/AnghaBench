#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {TYPE_1__* dvb; } ;
struct budget {int dummy; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;
struct TYPE_2__ {scalar_t__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int /*<<< orphan*/  Set22K (struct budget*,int) ; 

__attribute__((used)) static int budget_set_tone(struct dvb_frontend *fe,
			   enum fe_sec_tone_mode tone)
{
	struct budget* budget = (struct budget*) fe->dvb->priv;

	switch (tone) {
	case SEC_TONE_ON:
		Set22K (budget, 1);
		break;

	case SEC_TONE_OFF:
		Set22K (budget, 0);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}