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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  a2; scalar_t__ b2; int /*<<< orphan*/  a1; scalar_t__ b1; } ;
struct rcar_gen3_thermal_tsc {size_t id; TYPE_1__ coef; } ;

/* Variables and functions */
 int CTEMP_MASK ; 
 int EIO ; 
 int FIXPT_DIV (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ FIXPT_INT (int) ; 
 int FIXPT_TO_MCELSIUS (int) ; 
 int MCELSIUS (int) ; 
 int /*<<< orphan*/  REG_GEN3_TEMP ; 
 int rcar_gen3_thermal_read (struct rcar_gen3_thermal_tsc*,int /*<<< orphan*/ ) ; 
 int rcar_gen3_thermal_round (int) ; 
 int** thcode ; 

__attribute__((used)) static int rcar_gen3_thermal_get_temp(void *devdata, int *temp)
{
	struct rcar_gen3_thermal_tsc *tsc = devdata;
	int mcelsius, val;
	u32 reg;

	/* Read register and convert to mili Celsius */
	reg = rcar_gen3_thermal_read(tsc, REG_GEN3_TEMP) & CTEMP_MASK;

	if (reg <= thcode[tsc->id][1])
		val = FIXPT_DIV(FIXPT_INT(reg) - tsc->coef.b1,
				tsc->coef.a1);
	else
		val = FIXPT_DIV(FIXPT_INT(reg) - tsc->coef.b2,
				tsc->coef.a2);
	mcelsius = FIXPT_TO_MCELSIUS(val);

	/* Make sure we are inside specifications */
	if ((mcelsius < MCELSIUS(-40)) || (mcelsius > MCELSIUS(125)))
		return -EIO;

	/* Round value to device granularity setting */
	*temp = rcar_gen3_thermal_round(mcelsius);

	return 0;
}