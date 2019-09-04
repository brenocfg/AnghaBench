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
struct lgdt3305_state {int current_modulation; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LGDT3305_CR_LOCK_STATUS ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  lg_dbg (char*,int,char*) ; 
 scalar_t__ lg_fail (int) ; 
 int lgdt3305_read_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lgdt3305_read_cr_lock_status(struct lgdt3305_state *state,
					int *locked)
{
	u8 val;
	int ret;
	char *cr_lock_state = "";

	*locked = 0;

	ret = lgdt3305_read_reg(state, LGDT3305_CR_LOCK_STATUS, &val);
	if (lg_fail(ret))
		goto fail;

	switch (state->current_modulation) {
	case QAM_256:
	case QAM_64:
		if (val & (1 << 1))
			*locked = 1;

		switch (val & 0x07) {
		case 0:
			cr_lock_state = "QAM UNLOCK";
			break;
		case 4:
			cr_lock_state = "QAM 1stLock";
			break;
		case 6:
			cr_lock_state = "QAM 2ndLock";
			break;
		case 7:
			cr_lock_state = "QAM FinalLock";
			break;
		default:
			cr_lock_state = "CLOCKQAM-INVALID!";
			break;
		}
		break;
	case VSB_8:
		if (val & (1 << 7)) {
			*locked = 1;
			cr_lock_state = "CLOCKVSB";
		}
		break;
	default:
		ret = -EINVAL;
	}
	lg_dbg("(%d) %s\n", *locked, cr_lock_state);
fail:
	return ret;
}