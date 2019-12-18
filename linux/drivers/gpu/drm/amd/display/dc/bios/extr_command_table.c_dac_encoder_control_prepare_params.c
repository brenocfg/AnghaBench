#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  usPixelClock; int /*<<< orphan*/  ucAction; int /*<<< orphan*/  ucDacStandard; } ;
typedef  TYPE_1__ DAC_ENCODER_CONTROL_PS_ALLOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dac_encoder_control_prepare_params(
	DAC_ENCODER_CONTROL_PS_ALLOCATION *params,
	bool enable,
	uint32_t pixel_clock,
	uint8_t dac_standard)
{
	params->ucDacStandard = dac_standard;
	if (enable)
		params->ucAction = ATOM_ENABLE;
	else
		params->ucAction = ATOM_DISABLE;

	/* We need to convert from KHz units into 10KHz units
	 * it looks as if the TvControl do not care about pixel clock
	 */
	params->usPixelClock = cpu_to_le16((uint16_t)(pixel_clock / 10));
}