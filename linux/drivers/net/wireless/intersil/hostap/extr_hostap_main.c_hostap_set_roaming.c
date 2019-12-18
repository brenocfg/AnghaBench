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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int host_roaming; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_RID_CNFROAMINGMODE ; 
 int /*<<< orphan*/  HFA384X_ROAMING_DISABLED ; 
 int /*<<< orphan*/  HFA384X_ROAMING_FIRMWARE ; 
 int /*<<< orphan*/  HFA384X_ROAMING_HOST ; 
 int hostap_set_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hostap_set_roaming(local_info_t *local)
{
	u16 val;

	switch (local->host_roaming) {
	case 1:
		val = HFA384X_ROAMING_HOST;
		break;
	case 2:
		val = HFA384X_ROAMING_DISABLED;
		break;
	case 0:
	default:
		val = HFA384X_ROAMING_FIRMWARE;
		break;
	}

	return hostap_set_word(local->dev, HFA384X_RID_CNFROAMINGMODE, val);
}