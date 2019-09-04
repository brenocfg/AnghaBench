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
typedef  int /*<<< orphan*/  u32 ;
struct led_classdev_flash {int dummy; } ;
struct as3645a {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AS_FAULT_INFO_INDICATOR_LED ; 
 int AS_FAULT_INFO_INDUCTOR_PEAK_LIMIT ; 
 int AS_FAULT_INFO_LED_AMOUNT ; 
 int AS_FAULT_INFO_OVER_TEMPERATURE ; 
 int AS_FAULT_INFO_OVER_VOLTAGE ; 
 int /*<<< orphan*/  AS_FAULT_INFO_REG ; 
 int AS_FAULT_INFO_SHORT_CIRCUIT ; 
 int AS_FAULT_INFO_TIMEOUT ; 
 int /*<<< orphan*/  LED_FAULT_INDICATOR ; 
 int /*<<< orphan*/  LED_FAULT_INPUT_VOLTAGE ; 
 int /*<<< orphan*/  LED_FAULT_OVER_CURRENT ; 
 int /*<<< orphan*/  LED_FAULT_OVER_TEMPERATURE ; 
 int /*<<< orphan*/  LED_FAULT_TIMEOUT ; 
 int as3645a_read (struct as3645a*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct as3645a* fled_to_as3645a (struct led_classdev_flash*) ; 

__attribute__((used)) static int as3645a_get_fault(struct led_classdev_flash *fled, u32 *fault)
{
	struct as3645a *flash = fled_to_as3645a(fled);
	int rval;

	/* NOTE: reading register clears fault status */
	rval = as3645a_read(flash, AS_FAULT_INFO_REG);
	if (rval < 0)
		return rval;

	if (rval & AS_FAULT_INFO_INDUCTOR_PEAK_LIMIT)
		*fault |= LED_FAULT_OVER_CURRENT;

	if (rval & AS_FAULT_INFO_INDICATOR_LED)
		*fault |= LED_FAULT_INDICATOR;

	dev_dbg(&flash->client->dev, "%u connected LEDs\n",
		rval & AS_FAULT_INFO_LED_AMOUNT ? 2 : 1);

	if (rval & AS_FAULT_INFO_TIMEOUT)
		*fault |= LED_FAULT_TIMEOUT;

	if (rval & AS_FAULT_INFO_OVER_TEMPERATURE)
		*fault |= LED_FAULT_OVER_TEMPERATURE;

	if (rval & AS_FAULT_INFO_SHORT_CIRCUIT)
		*fault |= LED_FAULT_OVER_CURRENT;

	if (rval & AS_FAULT_INFO_OVER_VOLTAGE)
		*fault |= LED_FAULT_INPUT_VOLTAGE;

	return rval;
}