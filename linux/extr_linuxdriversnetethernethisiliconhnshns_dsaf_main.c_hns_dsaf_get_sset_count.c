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
struct dsaf_device {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 int AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int DSAF_STATIC_NUM ; 
 int DSAF_V2_STATIC_NUM ; 
 int ETH_SS_STATS ; 

int hns_dsaf_get_sset_count(struct dsaf_device *dsaf_dev, int stringset)
{
	bool is_ver1 = AE_IS_VER1(dsaf_dev->dsaf_ver);

	if (stringset == ETH_SS_STATS) {
		if (is_ver1)
			return DSAF_STATIC_NUM;
		else
			return DSAF_V2_STATIC_NUM;
	}
	return 0;
}