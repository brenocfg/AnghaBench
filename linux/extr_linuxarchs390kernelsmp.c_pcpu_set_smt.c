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
struct TYPE_2__ {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGP_SET_MULTI_THREADING ; 
 int __pcpu_sigp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_1__* pcpu_devices ; 
 unsigned int smp_cpu_mt_shift ; 
 unsigned int smp_cpu_mtid ; 
 int /*<<< orphan*/  stap () ; 

__attribute__((used)) static int pcpu_set_smt(unsigned int mtid)
{
	int cc;

	if (smp_cpu_mtid == mtid)
		return 0;
	cc = __pcpu_sigp(0, SIGP_SET_MULTI_THREADING, mtid, NULL);
	if (cc == 0) {
		smp_cpu_mtid = mtid;
		smp_cpu_mt_shift = 0;
		while (smp_cpu_mtid >= (1U << smp_cpu_mt_shift))
			smp_cpu_mt_shift++;
		pcpu_devices[0].address = stap();
	}
	return cc;
}