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
struct lgdt3305_state {int dummy; } ;
struct dtv_frontend_properties {int modulation; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LGDT3305_DGTL_AGC_REF_1 ; 
 int /*<<< orphan*/  LGDT3305_DGTL_AGC_REF_2 ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  lg_dbg (char*,int) ; 
 int /*<<< orphan*/  lgdt3305_write_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lgdt3305_passband_digital_agc(struct lgdt3305_state *state,
					 struct dtv_frontend_properties *p)
{
	u16 agc_ref;

	switch (p->modulation) {
	case VSB_8:
		agc_ref = 0x32c4;
		break;
	case QAM_64:
		agc_ref = 0x2a00;
		break;
	case QAM_256:
		agc_ref = 0x2a80;
		break;
	default:
		return -EINVAL;
	}

	lg_dbg("agc ref: 0x%04x\n", agc_ref);

	lgdt3305_write_reg(state, LGDT3305_DGTL_AGC_REF_1, agc_ref >> 8);
	lgdt3305_write_reg(state, LGDT3305_DGTL_AGC_REF_2, agc_ref & 0xff);

	return 0;
}