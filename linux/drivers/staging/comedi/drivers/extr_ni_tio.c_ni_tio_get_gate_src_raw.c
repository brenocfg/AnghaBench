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
struct ni_gpct {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int ni_tio_get_gate2_mode (struct ni_gpct*) ; 
 unsigned int ni_tio_get_gate2_val (struct ni_gpct*) ; 
 unsigned int ni_tio_get_gate_mode (struct ni_gpct*) ; 
 unsigned int ni_tio_get_gate_val (struct ni_gpct*) ; 

__attribute__((used)) static int ni_tio_get_gate_src_raw(struct ni_gpct *counter,
				   unsigned int gate_index,
				   unsigned int *gate_source)
{
	switch (gate_index) {
	case 0:
		*gate_source = ni_tio_get_gate_mode(counter)
			     | ni_tio_get_gate_val(counter);
		break;
	case 1:
		*gate_source = ni_tio_get_gate2_mode(counter)
			     | ni_tio_get_gate2_val(counter);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}