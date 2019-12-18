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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct micro_battery {int flag; } ;

/* Variables and functions */
#define  MICRO_BATT_STATUS_CRITICAL 130 
#define  MICRO_BATT_STATUS_HIGH 129 
#define  MICRO_BATT_STATUS_LOW 128 
 struct micro_battery* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_capacity(struct power_supply *b)
{
	struct micro_battery *mb = dev_get_drvdata(b->dev.parent);

	switch (mb->flag & 0x07) {
	case MICRO_BATT_STATUS_HIGH:
		return 100;
		break;
	case MICRO_BATT_STATUS_LOW:
		return 50;
		break;
	case MICRO_BATT_STATUS_CRITICAL:
		return 5;
		break;
	default:
		break;
	}
	return 0;
}