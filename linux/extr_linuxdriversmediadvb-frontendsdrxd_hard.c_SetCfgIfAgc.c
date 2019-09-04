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
struct drxd_state {int dummy; } ;
struct SCfgAgc {int outputLevel; scalar_t__ ctrlMode; scalar_t__ maxOutputLevel; scalar_t__ minOutputLevel; int speed; int settleLevel; } ;

/* Variables and functions */
 scalar_t__ AGC_CTRL_AUTO ; 
 scalar_t__ AGC_CTRL_USER ; 
 int DRXD_FE_CTRL_MAX ; 
 int FE_AG_REG_AG_MODE_LOP_MODE_4_DYNAMIC ; 
 int FE_AG_REG_AG_MODE_LOP_MODE_4_STATIC ; 
 int FE_AG_REG_AG_MODE_LOP_MODE_4__M ; 
 int /*<<< orphan*/  FE_AG_REG_AG_MODE_LOP__A ; 
 int /*<<< orphan*/  FE_AG_REG_EGC_FAS_DEC__A ; 
 int /*<<< orphan*/  FE_AG_REG_EGC_FAS_INC__A ; 
 int /*<<< orphan*/  FE_AG_REG_EGC_RUR_CNT__A ; 
 int /*<<< orphan*/  FE_AG_REG_EGC_SET_LVL__A ; 
 int FE_AG_REG_EGC_SET_LVL__M ; 
 int /*<<< orphan*/  FE_AG_REG_EGC_SLO_DEC__A ; 
 int /*<<< orphan*/  FE_AG_REG_EGC_SLO_INC__A ; 
 int /*<<< orphan*/  FE_AG_REG_GC1_AGC_OFF__A ; 
 int /*<<< orphan*/  FE_AG_REG_GC1_AGC_RIC__A ; 
 int /*<<< orphan*/  FE_AG_REG_PM1_AGC_WRI__A ; 
 int FE_AG_REG_PM1_AGC_WRI__M ; 
 int Read16 (struct drxd_state*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SetCfgIfAgc(struct drxd_state *state, struct SCfgAgc *cfg)
{
	int status;

	if (cfg->outputLevel > DRXD_FE_CTRL_MAX)
		return -1;

	if (cfg->ctrlMode == AGC_CTRL_USER) {
		do {
			u16 FeAgRegPm1AgcWri;
			u16 FeAgRegAgModeLop;

			status = Read16(state, FE_AG_REG_AG_MODE_LOP__A, &FeAgRegAgModeLop, 0);
			if (status < 0)
				break;
			FeAgRegAgModeLop &= (~FE_AG_REG_AG_MODE_LOP_MODE_4__M);
			FeAgRegAgModeLop |= FE_AG_REG_AG_MODE_LOP_MODE_4_STATIC;
			status = Write16(state, FE_AG_REG_AG_MODE_LOP__A, FeAgRegAgModeLop, 0);
			if (status < 0)
				break;

			FeAgRegPm1AgcWri = (u16) (cfg->outputLevel &
						  FE_AG_REG_PM1_AGC_WRI__M);
			status = Write16(state, FE_AG_REG_PM1_AGC_WRI__A, FeAgRegPm1AgcWri, 0);
			if (status < 0)
				break;
		} while (0);
	} else if (cfg->ctrlMode == AGC_CTRL_AUTO) {
		if (((cfg->maxOutputLevel) < (cfg->minOutputLevel)) ||
		    ((cfg->maxOutputLevel) > DRXD_FE_CTRL_MAX) ||
		    ((cfg->speed) > DRXD_FE_CTRL_MAX) ||
		    ((cfg->settleLevel) > DRXD_FE_CTRL_MAX)
		    )
			return -1;
		do {
			u16 FeAgRegAgModeLop;
			u16 FeAgRegEgcSetLvl;
			u16 slope, offset;

			/* == Mode == */

			status = Read16(state, FE_AG_REG_AG_MODE_LOP__A, &FeAgRegAgModeLop, 0);
			if (status < 0)
				break;
			FeAgRegAgModeLop &= (~FE_AG_REG_AG_MODE_LOP_MODE_4__M);
			FeAgRegAgModeLop |=
			    FE_AG_REG_AG_MODE_LOP_MODE_4_DYNAMIC;
			status = Write16(state, FE_AG_REG_AG_MODE_LOP__A, FeAgRegAgModeLop, 0);
			if (status < 0)
				break;

			/* == Settle level == */

			FeAgRegEgcSetLvl = (u16) ((cfg->settleLevel >> 1) &
						  FE_AG_REG_EGC_SET_LVL__M);
			status = Write16(state, FE_AG_REG_EGC_SET_LVL__A, FeAgRegEgcSetLvl, 0);
			if (status < 0)
				break;

			/* == Min/Max == */

			slope = (u16) ((cfg->maxOutputLevel -
					cfg->minOutputLevel) / 2);
			offset = (u16) ((cfg->maxOutputLevel +
					 cfg->minOutputLevel) / 2 - 511);

			status = Write16(state, FE_AG_REG_GC1_AGC_RIC__A, slope, 0);
			if (status < 0)
				break;
			status = Write16(state, FE_AG_REG_GC1_AGC_OFF__A, offset, 0);
			if (status < 0)
				break;

			/* == Speed == */
			{
				const u16 maxRur = 8;
				static const u16 slowIncrDecLUT[] = {
					3, 4, 4, 5, 6 };
				static const u16 fastIncrDecLUT[] = {
					14, 15, 15, 16,
					17, 18, 18, 19,
					20, 21, 22, 23,
					24, 26, 27, 28,
					29, 31
				};

				u16 fineSteps = (DRXD_FE_CTRL_MAX + 1) /
				    (maxRur + 1);
				u16 fineSpeed = (u16) (cfg->speed -
						       ((cfg->speed /
							 fineSteps) *
							fineSteps));
				u16 invRurCount = (u16) (cfg->speed /
							 fineSteps);
				u16 rurCount;
				if (invRurCount > maxRur) {
					rurCount = 0;
					fineSpeed += fineSteps;
				} else {
					rurCount = maxRur - invRurCount;
				}

				/*
				   fastInc = default *
				   (2^(fineSpeed/fineSteps))
				   => range[default...2*default>
				   slowInc = default *
				   (2^(fineSpeed/fineSteps))
				 */
				{
					u16 fastIncrDec =
					    fastIncrDecLUT[fineSpeed /
							   ((fineSteps /
							     (14 + 1)) + 1)];
					u16 slowIncrDec =
					    slowIncrDecLUT[fineSpeed /
							   (fineSteps /
							    (3 + 1))];

					status = Write16(state, FE_AG_REG_EGC_RUR_CNT__A, rurCount, 0);
					if (status < 0)
						break;
					status = Write16(state, FE_AG_REG_EGC_FAS_INC__A, fastIncrDec, 0);
					if (status < 0)
						break;
					status = Write16(state, FE_AG_REG_EGC_FAS_DEC__A, fastIncrDec, 0);
					if (status < 0)
						break;
					status = Write16(state, FE_AG_REG_EGC_SLO_INC__A, slowIncrDec, 0);
					if (status < 0)
						break;
					status = Write16(state, FE_AG_REG_EGC_SLO_DEC__A, slowIncrDec, 0);
					if (status < 0)
						break;
				}
			}
		} while (0);

	} else {
		/* No OFF mode for IF control */
		return -1;
	}
	return status;
}