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
struct ni_gpct {struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NI_GPCT_DISABLED_GATE_SELECT ; 
 int /*<<< orphan*/  ni_tio_has_gate2_registers (struct ni_gpct_device*) ; 
 int /*<<< orphan*/  ni_tio_set_gate2_mode (struct ni_gpct*,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_set_gate2_raw (struct ni_gpct*,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_set_gate_mode (struct ni_gpct*,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_set_gate_raw (struct ni_gpct*,unsigned int) ; 

int ni_tio_set_gate_src_raw(struct ni_gpct *counter,
			    unsigned int gate, unsigned int src)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;

	switch (gate) {
	case 0:
		/* 1.  start by disabling gate */
		ni_tio_set_gate_mode(counter, NI_GPCT_DISABLED_GATE_SELECT);
		/* 2.  set the requested gate source */
		ni_tio_set_gate_raw(counter, src);
		/* 3.  reenable & set mode to starts things back up */
		ni_tio_set_gate_mode(counter, src);
		break;
	case 1:
		if (!ni_tio_has_gate2_registers(counter_dev))
			return -EINVAL;

		/* 1.  start by disabling gate */
		ni_tio_set_gate2_mode(counter, NI_GPCT_DISABLED_GATE_SELECT);
		/* 2.  set the requested gate source */
		ni_tio_set_gate2_raw(counter, src);
		/* 3.  reenable & set mode to starts things back up */
		ni_tio_set_gate2_mode(counter, src);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}