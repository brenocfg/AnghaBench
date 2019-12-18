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

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OT_EC_BT_MASK ; 
 int /*<<< orphan*/  OT_EC_GPS_MASK ; 
 int /*<<< orphan*/  OT_EC_WIFI_MASK ; 
 int /*<<< orphan*/  OT_EC_WWAN_MASK ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RFKILL_TYPE_BLUETOOTH ; 
 int /*<<< orphan*/  RFKILL_TYPE_GPS ; 
 int /*<<< orphan*/  RFKILL_TYPE_WLAN ; 
 int /*<<< orphan*/  RFKILL_TYPE_WWAN ; 
 int /*<<< orphan*/ * bt_rfkill ; 
 int /*<<< orphan*/ * gps_rfkill ; 
 int /*<<< orphan*/  oaktrail_rfkill_cleanup () ; 
 int /*<<< orphan*/ * oaktrail_rfkill_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wifi_rfkill ; 
 int /*<<< orphan*/ * wwan_rfkill ; 

__attribute__((used)) static int oaktrail_rfkill_init(void)
{
	int ret;

	wifi_rfkill = oaktrail_rfkill_new("oaktrail-wifi",
					  RFKILL_TYPE_WLAN,
					  OT_EC_WIFI_MASK);
	if (IS_ERR(wifi_rfkill)) {
		ret = PTR_ERR(wifi_rfkill);
		wifi_rfkill = NULL;
		goto cleanup;
	}

	bt_rfkill = oaktrail_rfkill_new("oaktrail-bluetooth",
					RFKILL_TYPE_BLUETOOTH,
					OT_EC_BT_MASK);
	if (IS_ERR(bt_rfkill)) {
		ret = PTR_ERR(bt_rfkill);
		bt_rfkill = NULL;
		goto cleanup;
	}

	gps_rfkill = oaktrail_rfkill_new("oaktrail-gps",
					 RFKILL_TYPE_GPS,
					 OT_EC_GPS_MASK);
	if (IS_ERR(gps_rfkill)) {
		ret = PTR_ERR(gps_rfkill);
		gps_rfkill = NULL;
		goto cleanup;
	}

	wwan_rfkill = oaktrail_rfkill_new("oaktrail-wwan",
					  RFKILL_TYPE_WWAN,
					  OT_EC_WWAN_MASK);
	if (IS_ERR(wwan_rfkill)) {
		ret = PTR_ERR(wwan_rfkill);
		wwan_rfkill = NULL;
		goto cleanup;
	}

	return 0;

cleanup:
	oaktrail_rfkill_cleanup();
	return ret;
}