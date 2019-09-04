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
struct device {int dummy; } ;
struct as3645a {int /*<<< orphan*/  fled; TYPE_1__* client; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_CONTROL_REG ; 
 int /*<<< orphan*/  AS_CURRENT_SET_REG ; 
 int AS_FAULT_INFO_LED_AMOUNT ; 
 int /*<<< orphan*/  AS_FAULT_INFO_REG ; 
 int /*<<< orphan*/  AS_INDICATOR_AND_TIMER_REG ; 
 int /*<<< orphan*/  AS_MODE_INDICATOR ; 
 int EIO ; 
 int as3645a_get_fault (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int as3645a_read (struct as3645a*,int /*<<< orphan*/ ) ; 
 int as3645a_set_control (struct as3645a*,int /*<<< orphan*/ ,int) ; 
 int as3645a_set_current (struct as3645a*) ; 
 int as3645a_set_timeout (struct as3645a*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 

__attribute__((used)) static int as3645a_setup(struct as3645a *flash)
{
	struct device *dev = &flash->client->dev;
	u32 fault = 0;
	int rval;

	/* clear errors */
	rval = as3645a_read(flash, AS_FAULT_INFO_REG);
	if (rval < 0)
		return rval;

	dev_dbg(dev, "Fault info: %02x\n", rval);

	rval = as3645a_set_current(flash);
	if (rval < 0)
		return rval;

	rval = as3645a_set_timeout(flash);
	if (rval < 0)
		return rval;

	rval = as3645a_set_control(flash, AS_MODE_INDICATOR, false);
	if (rval < 0)
		return rval;

	/* read status */
	rval = as3645a_get_fault(&flash->fled, &fault);
	if (rval < 0)
		return rval;

	dev_dbg(dev, "AS_INDICATOR_AND_TIMER_REG: %02x\n",
		as3645a_read(flash, AS_INDICATOR_AND_TIMER_REG));
	dev_dbg(dev, "AS_CURRENT_SET_REG: %02x\n",
		as3645a_read(flash, AS_CURRENT_SET_REG));
	dev_dbg(dev, "AS_CONTROL_REG: %02x\n",
		as3645a_read(flash, AS_CONTROL_REG));

	return rval & ~AS_FAULT_INFO_LED_AMOUNT ? -EIO : 0;
}