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
struct ni_gpct {TYPE_1__* counter_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  variant; } ;

/* Variables and functions */
 int EINVAL ; 
 int ni_660x_gate2_to_generic_gate (unsigned int,unsigned int*) ; 
 int ni_660x_gate_to_generic_gate (unsigned int,unsigned int*) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int ni_m_gate2_to_generic_gate (unsigned int,unsigned int*) ; 
 int ni_m_gate_to_generic_gate (unsigned int,unsigned int*) ; 
 unsigned int ni_tio_get_gate2_mode (struct ni_gpct*) ; 
 unsigned int ni_tio_get_gate2_val (struct ni_gpct*) ; 
 unsigned int ni_tio_get_gate_mode (struct ni_gpct*) ; 
 unsigned int ni_tio_get_gate_val (struct ni_gpct*) ; 

__attribute__((used)) static int ni_tio_get_gate_src(struct ni_gpct *counter, unsigned int gate_index,
			       unsigned int *gate_source)
{
	unsigned int gate;
	int ret;

	switch (gate_index) {
	case 0:
		gate = ni_tio_get_gate_val(counter);
		switch (counter->counter_dev->variant) {
		case ni_gpct_variant_e_series:
		case ni_gpct_variant_m_series:
		default:
			ret = ni_m_gate_to_generic_gate(gate, gate_source);
			break;
		case ni_gpct_variant_660x:
			ret = ni_660x_gate_to_generic_gate(gate, gate_source);
			break;
		}
		if (ret)
			return ret;
		*gate_source |= ni_tio_get_gate_mode(counter);
		break;
	case 1:
		gate = ni_tio_get_gate2_val(counter);
		switch (counter->counter_dev->variant) {
		case ni_gpct_variant_e_series:
		case ni_gpct_variant_m_series:
		default:
			ret = ni_m_gate2_to_generic_gate(gate, gate_source);
			break;
		case ni_gpct_variant_660x:
			ret = ni_660x_gate2_to_generic_gate(gate, gate_source);
			break;
		}
		if (ret)
			return ret;
		*gate_source |= ni_tio_get_gate2_mode(counter);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}