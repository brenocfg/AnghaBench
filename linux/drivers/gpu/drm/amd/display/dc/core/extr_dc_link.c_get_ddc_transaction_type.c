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
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum ddc_transaction_type { ____Placeholder_ddc_transaction_type } ddc_transaction_type ;

/* Variables and functions */
 int DDC_TRANSACTION_TYPE_I2C ; 
 int DDC_TRANSACTION_TYPE_I2C_OVER_AUX ; 
 int DDC_TRANSACTION_TYPE_NONE ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 135 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 134 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 133 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 132 
#define  SIGNAL_TYPE_EDP 131 
#define  SIGNAL_TYPE_HDMI_TYPE_A 130 
#define  SIGNAL_TYPE_LVDS 129 
#define  SIGNAL_TYPE_RGB 128 

__attribute__((used)) static enum ddc_transaction_type get_ddc_transaction_type(
		enum signal_type sink_signal)
{
	enum ddc_transaction_type transaction_type = DDC_TRANSACTION_TYPE_NONE;

	switch (sink_signal) {
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
	case SIGNAL_TYPE_DVI_DUAL_LINK:
	case SIGNAL_TYPE_HDMI_TYPE_A:
	case SIGNAL_TYPE_LVDS:
	case SIGNAL_TYPE_RGB:
		transaction_type = DDC_TRANSACTION_TYPE_I2C;
		break;

	case SIGNAL_TYPE_DISPLAY_PORT:
	case SIGNAL_TYPE_EDP:
		transaction_type = DDC_TRANSACTION_TYPE_I2C_OVER_AUX;
		break;

	case SIGNAL_TYPE_DISPLAY_PORT_MST:
		/* MST does not use I2COverAux, but there is the
		 * SPECIAL use case for "immediate dwnstrm device
		 * access" (EPR#370830). */
		transaction_type = DDC_TRANSACTION_TYPE_I2C_OVER_AUX;
		break;

	default:
		break;
	}

	return transaction_type;
}