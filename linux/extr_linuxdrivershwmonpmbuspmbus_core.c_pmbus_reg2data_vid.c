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
struct pmbus_sensor {long data; } ;
struct pmbus_data {TYPE_1__* info; } ;
struct TYPE_2__ {int vrm_version; } ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (int,int) ; 
#define  vr11 130 
#define  vr12 129 
#define  vr13 128 

__attribute__((used)) static long pmbus_reg2data_vid(struct pmbus_data *data,
			       struct pmbus_sensor *sensor)
{
	long val = sensor->data;
	long rv = 0;

	switch (data->info->vrm_version) {
	case vr11:
		if (val >= 0x02 && val <= 0xb2)
			rv = DIV_ROUND_CLOSEST(160000 - (val - 2) * 625, 100);
		break;
	case vr12:
		if (val >= 0x01)
			rv = 250 + (val - 1) * 5;
		break;
	case vr13:
		if (val >= 0x01)
			rv = 500 + (val - 1) * 10;
		break;
	}
	return rv;
}