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
 unsigned int CR_CHAN (unsigned int) ; 
 int EINVAL ; 
 unsigned int NI_660X_MAX_RTSI_CHAN ; 
 unsigned int NI_660X_MAX_UP_DOWN_PIN ; 
 unsigned int NI_660X_NEXT_SRC_GATE2_SEL ; 
#define  NI_GPCT_LOGIC_LOW_GATE_SELECT 133 
#define  NI_GPCT_NEXT_OUT_GATE_SELECT 132 
#define  NI_GPCT_NEXT_SOURCE_GATE_SELECT 131 
 unsigned int NI_GPCT_RTSI_GATE_SELECT (unsigned int) ; 
#define  NI_GPCT_SELECTED_GATE_GATE_SELECT 130 
#define  NI_GPCT_SOURCE_PIN_i_GATE_SELECT 129 
 unsigned int NI_GPCT_UP_DOWN_PIN_GATE_SELECT (unsigned int) ; 
#define  NI_GPCT_UP_DOWN_PIN_i_GATE_SELECT 128 
 int /*<<< orphan*/  ni_tio_set_gate2_raw (struct ni_gpct*,unsigned int) ; 

__attribute__((used)) static int ni_660x_set_gate2(struct ni_gpct *counter, unsigned int gate_source)
{
	unsigned int chan = CR_CHAN(gate_source);
	unsigned int gate2_sel;
	unsigned int i;

	switch (chan) {
	case NI_GPCT_SOURCE_PIN_i_GATE_SELECT:
	case NI_GPCT_UP_DOWN_PIN_i_GATE_SELECT:
	case NI_GPCT_SELECTED_GATE_GATE_SELECT:
	case NI_GPCT_NEXT_OUT_GATE_SELECT:
	case NI_GPCT_LOGIC_LOW_GATE_SELECT:
		gate2_sel = chan & 0x1f;
		break;
	case NI_GPCT_NEXT_SOURCE_GATE_SELECT:
		gate2_sel = NI_660X_NEXT_SRC_GATE2_SEL;
		break;
	default:
		for (i = 0; i <= NI_660X_MAX_RTSI_CHAN; ++i) {
			if (chan == NI_GPCT_RTSI_GATE_SELECT(i)) {
				gate2_sel = chan & 0x1f;
				break;
			}
		}
		if (i <= NI_660X_MAX_RTSI_CHAN)
			break;
		for (i = 0; i <= NI_660X_MAX_UP_DOWN_PIN; ++i) {
			if (chan == NI_GPCT_UP_DOWN_PIN_GATE_SELECT(i)) {
				gate2_sel = chan & 0x1f;
				break;
			}
		}
		if (i <= NI_660X_MAX_UP_DOWN_PIN)
			break;
		return -EINVAL;
	}
	ni_tio_set_gate2_raw(counter, gate2_sel);
	return 0;
}