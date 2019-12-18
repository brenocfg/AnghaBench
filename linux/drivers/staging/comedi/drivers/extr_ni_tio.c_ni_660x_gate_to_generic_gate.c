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

/* Variables and functions */
 int EINVAL ; 
#define  NI_660X_GATE_PIN_I_GATE_SEL 132 
#define  NI_660X_LOGIC_LOW_GATE_SEL 131 
 unsigned int NI_660X_MAX_GATE_PIN ; 
 unsigned int NI_660X_MAX_RTSI_CHAN ; 
#define  NI_660X_NEXT_OUT_GATE_SEL 130 
#define  NI_660X_NEXT_SRC_GATE_SEL 129 
 unsigned int NI_660X_PIN_GATE_SEL (unsigned int) ; 
 unsigned int NI_660X_RTSI_GATE_SEL (unsigned int) ; 
#define  NI_660X_SRC_PIN_I_GATE_SEL 128 
 unsigned int NI_GPCT_GATE_PIN_GATE_SELECT (unsigned int) ; 
 unsigned int NI_GPCT_GATE_PIN_i_GATE_SELECT ; 
 unsigned int NI_GPCT_LOGIC_LOW_GATE_SELECT ; 
 unsigned int NI_GPCT_NEXT_OUT_GATE_SELECT ; 
 unsigned int NI_GPCT_NEXT_SOURCE_GATE_SELECT ; 
 unsigned int NI_GPCT_RTSI_GATE_SELECT (unsigned int) ; 
 unsigned int NI_GPCT_SOURCE_PIN_i_GATE_SELECT ; 

__attribute__((used)) static int ni_660x_gate_to_generic_gate(unsigned int gate, unsigned int *src)
{
	unsigned int source;
	unsigned int i;

	switch (gate) {
	case NI_660X_SRC_PIN_I_GATE_SEL:
		source = NI_GPCT_SOURCE_PIN_i_GATE_SELECT;
		break;
	case NI_660X_GATE_PIN_I_GATE_SEL:
		source = NI_GPCT_GATE_PIN_i_GATE_SELECT;
		break;
	case NI_660X_NEXT_SRC_GATE_SEL:
		source = NI_GPCT_NEXT_SOURCE_GATE_SELECT;
		break;
	case NI_660X_NEXT_OUT_GATE_SEL:
		source = NI_GPCT_NEXT_OUT_GATE_SELECT;
		break;
	case NI_660X_LOGIC_LOW_GATE_SEL:
		source = NI_GPCT_LOGIC_LOW_GATE_SELECT;
		break;
	default:
		for (i = 0; i <= NI_660X_MAX_RTSI_CHAN; ++i) {
			if (gate == NI_660X_RTSI_GATE_SEL(i)) {
				source = NI_GPCT_RTSI_GATE_SELECT(i);
				break;
			}
		}
		if (i <= NI_660X_MAX_RTSI_CHAN)
			break;
		for (i = 0; i <= NI_660X_MAX_GATE_PIN; ++i) {
			if (gate == NI_660X_PIN_GATE_SEL(i)) {
				source = NI_GPCT_GATE_PIN_GATE_SELECT(i);
				break;
			}
		}
		if (i <= NI_660X_MAX_GATE_PIN)
			break;
		return -EINVAL;
	}
	*src = source;
	return 0;
}