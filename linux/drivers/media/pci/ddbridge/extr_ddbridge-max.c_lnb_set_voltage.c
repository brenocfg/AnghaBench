#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct ddb {TYPE_2__* link; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_3__ {int* oldvoltage; int /*<<< orphan*/ * voltage; } ;
struct TYPE_4__ {TYPE_1__ lnb; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LNB_CMD_HIGH ; 
 int /*<<< orphan*/  LNB_CMD_LOW ; 
 int /*<<< orphan*/  LNB_CMD_OFF ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  lnb_command (struct ddb*,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lnb_set_voltage(struct ddb *dev, u32 link, u32 input,
			   enum fe_sec_voltage voltage)
{
	int s = 0;

	if (dev->link[link].lnb.oldvoltage[input] == voltage)
		return 0;
	switch (voltage) {
	case SEC_VOLTAGE_OFF:
		if (dev->link[link].lnb.voltage[input])
			return 0;
		lnb_command(dev, link, input, LNB_CMD_OFF);
		break;
	case SEC_VOLTAGE_13:
		lnb_command(dev, link, input, LNB_CMD_LOW);
		break;
	case SEC_VOLTAGE_18:
		lnb_command(dev, link, input, LNB_CMD_HIGH);
		break;
	default:
		s = -EINVAL;
		break;
	}
	dev->link[link].lnb.oldvoltage[input] = voltage;
	return s;
}