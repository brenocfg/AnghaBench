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
struct rcar_gen3_thermal_tsc {int dummy; } ;

/* Variables and functions */
 int CTSR_AOUT ; 
 int CTSR_PONM ; 
 int CTSR_THBGR ; 
 int CTSR_THSST ; 
 int CTSR_VMEN ; 
 int CTSR_VMST ; 
 int IRQ_TEMP2 ; 
 int IRQ_TEMPD1 ; 
 int /*<<< orphan*/  REG_GEN3_CTSR ; 
 int /*<<< orphan*/  REG_GEN3_IRQCTL ; 
 int /*<<< orphan*/  REG_GEN3_IRQEN ; 
 int /*<<< orphan*/  REG_GEN3_IRQMSK ; 
 int /*<<< orphan*/  rcar_gen3_thermal_write (struct rcar_gen3_thermal_tsc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rcar_gen3_thermal_init_r8a7795es1(struct rcar_gen3_thermal_tsc *tsc)
{
	rcar_gen3_thermal_write(tsc, REG_GEN3_CTSR,  CTSR_THBGR);
	rcar_gen3_thermal_write(tsc, REG_GEN3_CTSR,  0x0);

	usleep_range(1000, 2000);

	rcar_gen3_thermal_write(tsc, REG_GEN3_CTSR, CTSR_PONM);

	rcar_gen3_thermal_write(tsc, REG_GEN3_IRQCTL, 0x3F);
	rcar_gen3_thermal_write(tsc, REG_GEN3_IRQMSK, 0);
	rcar_gen3_thermal_write(tsc, REG_GEN3_IRQEN, IRQ_TEMPD1 | IRQ_TEMP2);

	rcar_gen3_thermal_write(tsc, REG_GEN3_CTSR,
				CTSR_PONM | CTSR_AOUT | CTSR_THBGR | CTSR_VMEN);

	usleep_range(100, 200);

	rcar_gen3_thermal_write(tsc, REG_GEN3_CTSR,
				CTSR_PONM | CTSR_AOUT | CTSR_THBGR | CTSR_VMEN |
				CTSR_VMST | CTSR_THSST);

	usleep_range(1000, 2000);
}