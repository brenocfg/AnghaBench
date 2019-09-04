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
struct cx88_core {int dummy; } ;
struct cx8802_dev {struct cx88_core* core; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;
struct TYPE_2__ {struct cx8802_dev* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MO_GP0_IO ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int samsung_smt_7020_set_tone(struct dvb_frontend *fe,
				     enum fe_sec_tone_mode tone)
{
	struct cx8802_dev *dev = fe->dvb->priv;
	struct cx88_core *core = dev->core;

	cx_set(MO_GP0_IO, 0x0800);

	switch (tone) {
	case SEC_TONE_ON:
		cx_set(MO_GP0_IO, 0x08);
		break;
	case SEC_TONE_OFF:
		cx_clear(MO_GP0_IO, 0x08);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}