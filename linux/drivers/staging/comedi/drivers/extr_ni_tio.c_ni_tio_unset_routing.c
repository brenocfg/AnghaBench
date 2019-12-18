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
struct ni_gpct_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NI_GATES_NAMES_BASE ; 
 unsigned int NI_GATES_NAMES_MAX ; 
 int /*<<< orphan*/  NI_GPCT_DISABLED_GATE_SELECT ; 
 int ni_tio_set_routing (struct ni_gpct_device*,unsigned int,int /*<<< orphan*/ ) ; 

int ni_tio_unset_routing(struct ni_gpct_device *counter_dev, unsigned int dest)
{
	if (dest >= NI_GATES_NAMES_BASE && dest <= NI_GATES_NAMES_MAX)
		/* Disable gate (via mode bits) and set to default 0-value */
		return ni_tio_set_routing(counter_dev, dest,
					  NI_GPCT_DISABLED_GATE_SELECT);
	/*
	 * This case is not possible through this interface.  A user must use
	 * INSN_CONFIG_SET_CLOCK_SRC instead.
	 * if (dest >= NI_CtrSource(0) && dest <= NI_CtrSource(-1))
	 *	return ni_tio_set_clock_src(counter, reg, period_ns);
	 */

	return -EINVAL;
}