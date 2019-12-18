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
typedef  int u64 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int /*<<< orphan*/  DBG_LOTS (char*,int,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  FIX32TOPRINT (int) ; 
 int /*<<< orphan*/ * sens_cpu_amps ; 
 int /*<<< orphan*/ * sens_cpu_temp ; 
 int /*<<< orphan*/ * sens_cpu_volts ; 
 int wf_sensor_get (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int read_one_cpu_vals(int cpu, s32 *temp, s32 *power)
{
	s32 dtemp, volts, amps;
	int rc;

	/* Get diode temperature */
	rc = wf_sensor_get(sens_cpu_temp[cpu], &dtemp);
	if (rc) {
		DBG("  CPU%d: temp reading error !\n", cpu);
		return -EIO;
	}
	DBG_LOTS("  CPU%d: temp   = %d.%03d\n", cpu, FIX32TOPRINT((dtemp)));
	*temp = dtemp;

	/* Get voltage */
	rc = wf_sensor_get(sens_cpu_volts[cpu], &volts);
	if (rc) {
		DBG("  CPU%d, volts reading error !\n", cpu);
		return -EIO;
	}
	DBG_LOTS("  CPU%d: volts  = %d.%03d\n", cpu, FIX32TOPRINT((volts)));

	/* Get current */
	rc = wf_sensor_get(sens_cpu_amps[cpu], &amps);
	if (rc) {
		DBG("  CPU%d, current reading error !\n", cpu);
		return -EIO;
	}
	DBG_LOTS("  CPU%d: amps   = %d.%03d\n", cpu, FIX32TOPRINT((amps)));

	/* Calculate power */

	/* Scale voltage and current raw sensor values according to fixed scales
	 * obtained in Darwin and calculate power from I and V
	 */
	*power = (((u64)volts) * ((u64)amps)) >> 16;

	DBG_LOTS("  CPU%d: power  = %d.%03d\n", cpu, FIX32TOPRINT((*power)));

	return 0;

}