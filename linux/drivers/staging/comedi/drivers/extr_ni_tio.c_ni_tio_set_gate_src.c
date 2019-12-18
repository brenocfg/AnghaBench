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
struct ni_gpct_device {int /*<<< orphan*/  variant; } ;
struct ni_gpct {struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 unsigned int CR_CHAN (unsigned int) ; 
 int EINVAL ; 
 unsigned int NI_GPCT_DISABLED_GATE_SELECT ; 
 int ni_660x_set_gate (struct ni_gpct*,int) ; 
 int ni_660x_set_gate2 (struct ni_gpct*,int) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int ni_m_set_gate (struct ni_gpct*,int) ; 
 int ni_m_set_gate2 (struct ni_gpct*,int) ; 
 int /*<<< orphan*/  ni_tio_has_gate2_registers (struct ni_gpct_device*) ; 
 int /*<<< orphan*/  ni_tio_set_gate2_mode (struct ni_gpct*,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_set_gate_mode (struct ni_gpct*,unsigned int) ; 

int ni_tio_set_gate_src(struct ni_gpct *counter,
			unsigned int gate, unsigned int src)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	/*
	 * mask off disable flag.  This high bit still passes CR_CHAN.
	 * Doing this allows one to both set the gate as disabled, but also
	 * change the route value of the gate.
	 */
	int chan = CR_CHAN(src) & (~NI_GPCT_DISABLED_GATE_SELECT);
	int ret;

	switch (gate) {
	case 0:
		/* 1.  start by disabling gate */
		ni_tio_set_gate_mode(counter, NI_GPCT_DISABLED_GATE_SELECT);
		/* 2.  set the requested gate source */
		switch (counter_dev->variant) {
		case ni_gpct_variant_e_series:
		case ni_gpct_variant_m_series:
			ret = ni_m_set_gate(counter, chan);
			break;
		case ni_gpct_variant_660x:
			ret = ni_660x_set_gate(counter, chan);
			break;
		default:
			return -EINVAL;
		}
		if (ret)
			return ret;
		/* 3.  reenable & set mode to starts things back up */
		ni_tio_set_gate_mode(counter, src);
		break;
	case 1:
		if (!ni_tio_has_gate2_registers(counter_dev))
			return -EINVAL;

		/* 1.  start by disabling gate */
		ni_tio_set_gate2_mode(counter, NI_GPCT_DISABLED_GATE_SELECT);
		/* 2.  set the requested gate source */
		switch (counter_dev->variant) {
		case ni_gpct_variant_m_series:
			ret = ni_m_set_gate2(counter, chan);
			break;
		case ni_gpct_variant_660x:
			ret = ni_660x_set_gate2(counter, chan);
			break;
		default:
			return -EINVAL;
		}
		if (ret)
			return ret;
		/* 3.  reenable & set mode to starts things back up */
		ni_tio_set_gate2_mode(counter, src);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}