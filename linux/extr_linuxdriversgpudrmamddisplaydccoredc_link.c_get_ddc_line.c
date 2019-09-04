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
struct ddc {int dummy; } ;
struct dc_link {int /*<<< orphan*/  ddc; } ;
typedef  enum channel_id { ____Placeholder_channel_id } channel_id ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int CHANNEL_ID_DDC1 ; 
 int CHANNEL_ID_DDC2 ; 
 int CHANNEL_ID_DDC3 ; 
 int CHANNEL_ID_DDC4 ; 
 int CHANNEL_ID_DDC5 ; 
 int CHANNEL_ID_DDC6 ; 
 int CHANNEL_ID_DDC_VGA ; 
 int CHANNEL_ID_I2C_PAD ; 
 int CHANNEL_ID_UNKNOWN ; 
#define  GPIO_DDC_LINE_DDC1 135 
#define  GPIO_DDC_LINE_DDC2 134 
#define  GPIO_DDC_LINE_DDC3 133 
#define  GPIO_DDC_LINE_DDC4 132 
#define  GPIO_DDC_LINE_DDC5 131 
#define  GPIO_DDC_LINE_DDC6 130 
#define  GPIO_DDC_LINE_DDC_VGA 129 
#define  GPIO_DDC_LINE_I2C_PAD 128 
 int dal_ddc_get_line (struct ddc*) ; 
 struct ddc* dal_ddc_service_get_ddc_pin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum channel_id get_ddc_line(struct dc_link *link)
{
	struct ddc *ddc;
	enum channel_id channel = CHANNEL_ID_UNKNOWN;

	ddc = dal_ddc_service_get_ddc_pin(link->ddc);

	if (ddc) {
		switch (dal_ddc_get_line(ddc)) {
		case GPIO_DDC_LINE_DDC1:
			channel = CHANNEL_ID_DDC1;
			break;
		case GPIO_DDC_LINE_DDC2:
			channel = CHANNEL_ID_DDC2;
			break;
		case GPIO_DDC_LINE_DDC3:
			channel = CHANNEL_ID_DDC3;
			break;
		case GPIO_DDC_LINE_DDC4:
			channel = CHANNEL_ID_DDC4;
			break;
		case GPIO_DDC_LINE_DDC5:
			channel = CHANNEL_ID_DDC5;
			break;
		case GPIO_DDC_LINE_DDC6:
			channel = CHANNEL_ID_DDC6;
			break;
		case GPIO_DDC_LINE_DDC_VGA:
			channel = CHANNEL_ID_DDC_VGA;
			break;
		case GPIO_DDC_LINE_I2C_PAD:
			channel = CHANNEL_ID_I2C_PAD;
			break;
		default:
			BREAK_TO_DEBUGGER();
			break;
		}
	}

	return channel;
}