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
struct lgdt3306a_state {int current_modulation; } ;
struct dtv_frontend_properties {int modulation; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QAM_256 131 
#define  QAM_64 130 
#define  QAM_AUTO 129 
#define  VSB_8 128 
 int /*<<< orphan*/  dbg_info (char*) ; 
 scalar_t__ lg_chkerr (int) ; 
 int lgdt3306a_set_qam (struct lgdt3306a_state*,int) ; 
 int lgdt3306a_set_vsb (struct lgdt3306a_state*) ; 

__attribute__((used)) static int lgdt3306a_set_modulation(struct lgdt3306a_state *state,
				   struct dtv_frontend_properties *p)
{
	int ret;

	dbg_info("\n");

	switch (p->modulation) {
	case VSB_8:
		ret = lgdt3306a_set_vsb(state);
		break;
	case QAM_64:
	case QAM_256:
	case QAM_AUTO:
		ret = lgdt3306a_set_qam(state, p->modulation);
		break;
	default:
		return -EINVAL;
	}
	if (lg_chkerr(ret))
		goto fail;

	state->current_modulation = p->modulation;

fail:
	return ret;
}