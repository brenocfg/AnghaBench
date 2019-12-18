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
struct lgdt3306a_state {int dummy; } ;
struct dtv_frontend_properties {int modulation; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QAM_256 131 
#define  QAM_64 130 
#define  QAM_AUTO 129 
#define  VSB_8 128 
 int /*<<< orphan*/  dbg_info (char*,int) ; 
 int lgdt3306a_set_inversion (struct lgdt3306a_state*,int) ; 
 int lgdt3306a_set_inversion_auto (struct lgdt3306a_state*,int) ; 

__attribute__((used)) static int lgdt3306a_spectral_inversion(struct lgdt3306a_state *state,
				       struct dtv_frontend_properties *p,
				       int inversion)
{
	int ret = 0;

	dbg_info("(%d)\n", inversion);
#if 0
	/*
	 * FGR - spectral_inversion defaults already set for VSB and QAM;
	 * can enable later if desired
	 */

	ret = lgdt3306a_set_inversion(state, inversion);

	switch (p->modulation) {
	case VSB_8:
		/* Manual only for VSB */
		ret = lgdt3306a_set_inversion_auto(state, 0);
		break;
	case QAM_64:
	case QAM_256:
	case QAM_AUTO:
		/* Auto ok for QAM */
		ret = lgdt3306a_set_inversion_auto(state, 1);
		break;
	default:
		ret = -EINVAL;
	}
#endif
	return ret;
}