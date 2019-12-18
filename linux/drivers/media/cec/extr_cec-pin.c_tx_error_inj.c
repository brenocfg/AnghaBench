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
typedef  scalar_t__ u8 ;
typedef  unsigned int u64 ;
typedef  size_t u16 ;
struct cec_pin {unsigned int* error_inj; scalar_t__** error_inj_args; scalar_t__ tx_bit; int tx_toggle; } ;

/* Variables and functions */
#define  CEC_ERROR_INJ_MODE_ALWAYS 130 
 unsigned int CEC_ERROR_INJ_MODE_MASK ; 
#define  CEC_ERROR_INJ_MODE_ONCE 129 
#define  CEC_ERROR_INJ_MODE_TOGGLE 128 
 size_t cec_pin_tx_error_inj (struct cec_pin*) ; 

__attribute__((used)) static bool tx_error_inj(struct cec_pin *pin, unsigned int mode_offset,
			 int arg_idx, u8 *arg)
{
#ifdef CONFIG_CEC_PIN_ERROR_INJ
	u16 cmd = cec_pin_tx_error_inj(pin);
	u64 e = pin->error_inj[cmd];
	unsigned int mode = (e >> mode_offset) & CEC_ERROR_INJ_MODE_MASK;

	if (arg_idx >= 0) {
		u8 pos = pin->error_inj_args[cmd][arg_idx];

		if (arg)
			*arg = pos;
		else if (pos != pin->tx_bit)
			return false;
	}

	switch (mode) {
	case CEC_ERROR_INJ_MODE_ONCE:
		pin->error_inj[cmd] &=
			~(CEC_ERROR_INJ_MODE_MASK << mode_offset);
		return true;
	case CEC_ERROR_INJ_MODE_ALWAYS:
		return true;
	case CEC_ERROR_INJ_MODE_TOGGLE:
		return pin->tx_toggle;
	default:
		return false;
	}
#else
	return false;
#endif
}