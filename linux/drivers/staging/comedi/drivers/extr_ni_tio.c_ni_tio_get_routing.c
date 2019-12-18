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
struct ni_gpct_device {struct ni_gpct* counters; } ;
struct ni_gpct {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NI_COUNTER_NAMES_BASE ; 
 unsigned int NI_CtrA (int /*<<< orphan*/ ) ; 
 unsigned int NI_CtrAux (int) ; 
 unsigned int NI_CtrGate (int) ; 
 unsigned int NI_CtrZ (int) ; 
 unsigned int NI_MAX_COUNTERS ; 
 int ni_tio_get_gate_src_raw (struct ni_gpct*,int,unsigned int*) ; 
 int ni_tio_get_other_src (struct ni_gpct*,unsigned int,unsigned int*) ; 

int ni_tio_get_routing(struct ni_gpct_device *counter_dev, unsigned int dest)
{
	/* we need to know the actual counter below... */
	int ctr_index = (dest - NI_COUNTER_NAMES_BASE) % NI_MAX_COUNTERS;
	struct ni_gpct *counter = &counter_dev->counters[ctr_index];
	int ret = 1;
	unsigned int reg;

	if (dest >= NI_CtrA(0) && dest <= NI_CtrZ(-1)) {
		ret = ni_tio_get_other_src(counter, dest, &reg);
	} else if (dest >= NI_CtrGate(0) && dest <= NI_CtrGate(-1)) {
		ret = ni_tio_get_gate_src_raw(counter, 0, &reg);
	} else if (dest >= NI_CtrAux(0) && dest <= NI_CtrAux(-1)) {
		ret = ni_tio_get_gate_src_raw(counter, 1, &reg);
	/*
	 * This case is not possible through this interface.  A user must use
	 * INSN_CONFIG_SET_CLOCK_SRC instead.
	 * } else if (dest >= NI_CtrSource(0) && dest <= NI_CtrSource(-1)) {
	 *	ret = ni_tio_set_clock_src(counter, &reg, &period_ns);
	 */
	}

	if (ret)
		return -EINVAL;

	return reg;
}