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
typedef  int /*<<< orphan*/  u8 ;
struct edid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_for_each_detailed_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  monitor_name ; 

__attribute__((used)) static int get_monitor_name(struct edid *edid, char name[13])
{
	char *edid_name = NULL;
	int mnl;

	if (!edid || !name)
		return 0;

	drm_for_each_detailed_block((u8 *)edid, monitor_name, &edid_name);
	for (mnl = 0; edid_name && mnl < 13; mnl++) {
		if (edid_name[mnl] == 0x0a)
			break;

		name[mnl] = edid_name[mnl];
	}

	return mnl;
}