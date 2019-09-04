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
typedef  size_t uint32_t ;
struct ve_spc_opp {size_t freq; size_t u_volt; } ;
struct TYPE_2__ {size_t* num_opps; struct ve_spc_opp** opps; } ;

/* Variables and functions */
 size_t A15_PERFVAL_BASE ; 
 size_t A7_PERFVAL_BASE ; 
 int ENOMEM ; 
 size_t FREQ_MASK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MAX_OPPS ; 
 size_t MULT_FACTOR ; 
 int /*<<< orphan*/  SYSCFG_SCC ; 
 size_t VOLT_SHIFT ; 
 scalar_t__ cluster_is_a15 (size_t) ; 
 TYPE_1__* info ; 
 struct ve_spc_opp* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 size_t ve_spc_read_sys_cfg (int /*<<< orphan*/ ,size_t,size_t*) ; 

__attribute__((used)) static int ve_spc_populate_opps(uint32_t cluster)
{
	uint32_t data = 0, off, ret, idx;
	struct ve_spc_opp *opps;

	opps = kcalloc(MAX_OPPS, sizeof(*opps), GFP_KERNEL);
	if (!opps)
		return -ENOMEM;

	info->opps[cluster] = opps;

	off = cluster_is_a15(cluster) ? A15_PERFVAL_BASE : A7_PERFVAL_BASE;
	for (idx = 0; idx < MAX_OPPS; idx++, off += 4, opps++) {
		ret = ve_spc_read_sys_cfg(SYSCFG_SCC, off, &data);
		if (!ret) {
			opps->freq = (data & FREQ_MASK) * MULT_FACTOR;
			opps->u_volt = (data >> VOLT_SHIFT) * 1000;
		} else {
			break;
		}
	}
	info->num_opps[cluster] = idx;

	return ret;
}