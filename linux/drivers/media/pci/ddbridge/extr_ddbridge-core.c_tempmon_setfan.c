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
typedef  int u32 ;
struct ddb_link {int overtemperature_error; int* temp_tab; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEMPMON_CONTROL ; 
 int TEMPMON_CONTROL_OVERTEMP ; 
 int /*<<< orphan*/  TEMPMON_FANCONTROL ; 
 int /*<<< orphan*/  TEMPMON_SENSOR0 ; 
 int /*<<< orphan*/  TEMPMON_SENSOR1 ; 
 int ddblreadl (struct ddb_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddblwritel (struct ddb_link*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void tempmon_setfan(struct ddb_link *link)
{
	u32 temp, temp2, pwm;

	if ((ddblreadl(link, TEMPMON_CONTROL) &
	    TEMPMON_CONTROL_OVERTEMP) != 0) {
		dev_info(link->dev->dev, "Over temperature condition\n");
		link->overtemperature_error = 1;
	}
	temp  = (ddblreadl(link, TEMPMON_SENSOR0) >> 8) & 0xFF;
	if (temp & 0x80)
		temp = 0;
	temp2  = (ddblreadl(link, TEMPMON_SENSOR1) >> 8) & 0xFF;
	if (temp2 & 0x80)
		temp2 = 0;
	if (temp2 > temp)
		temp = temp2;

	pwm = (ddblreadl(link, TEMPMON_FANCONTROL) >> 8) & 0x0F;
	if (pwm > 10)
		pwm = 10;

	if (temp >= link->temp_tab[pwm]) {
		while (pwm < 10 && temp >= link->temp_tab[pwm + 1])
			pwm += 1;
	} else {
		while (pwm > 1 && temp < link->temp_tab[pwm - 2])
			pwm -= 1;
	}
	ddblwritel(link, (pwm << 8), TEMPMON_FANCONTROL);
}