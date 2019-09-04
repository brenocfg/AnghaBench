#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pmf_args {int count; TYPE_1__* u; } ;
struct TYPE_4__ {unsigned long frequency; } ;
struct TYPE_3__ {scalar_t__* p; } ;

/* Variables and functions */
 int CPUFREQ_HIGH ; 
 int /*<<< orphan*/  DBG (char*,int) ; 
 int HZ ; 
 TYPE_2__* g5_cpu_freqs ; 
 int g5_pmode_cur ; 
 int /*<<< orphan*/  g5_switch_volt (int) ; 
 int jiffies ; 
 int /*<<< orphan*/  pfunc_cpu_setfreq_high ; 
 int /*<<< orphan*/  pfunc_cpu_setfreq_low ; 
 int /*<<< orphan*/  pfunc_slewing_done ; 
 int pmf_call_one (int /*<<< orphan*/ ,struct pmf_args*) ; 
 unsigned long ppc_proc_freq ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  time_after (int,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int g5_pfunc_switch_freq(int speed_mode)
{
	struct pmf_args args;
	u32 done = 0;
	unsigned long timeout;
	int rc;

	DBG("g5_pfunc_switch_freq(%d)\n", speed_mode);

	/* If frequency is going up, first ramp up the voltage */
	if (speed_mode < g5_pmode_cur)
		g5_switch_volt(speed_mode);

	/* Do it */
	if (speed_mode == CPUFREQ_HIGH)
		rc = pmf_call_one(pfunc_cpu_setfreq_high, NULL);
	else
		rc = pmf_call_one(pfunc_cpu_setfreq_low, NULL);

	if (rc)
		pr_warn("pfunc switch error %d\n", rc);

	/* It's an irq GPIO so we should be able to just block here,
	 * I'll do that later after I've properly tested the IRQ code for
	 * platform functions
	 */
	timeout = jiffies + HZ/10;
	while(!time_after(jiffies, timeout)) {
		args.count = 1;
		args.u[0].p = &done;
		pmf_call_one(pfunc_slewing_done, &args);
		if (done)
			break;
		usleep_range(500, 500);
	}
	if (done == 0)
		pr_warn("Timeout in clock slewing !\n");

	/* If frequency is going down, last ramp the voltage */
	if (speed_mode > g5_pmode_cur)
		g5_switch_volt(speed_mode);

	g5_pmode_cur = speed_mode;
	ppc_proc_freq = g5_cpu_freqs[speed_mode].frequency * 1000ul;

	return 0;
}