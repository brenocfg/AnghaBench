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
struct TYPE_2__ {int type; } ;
struct kempld_device_data {TYPE_1__ info; } ;

/* Variables and functions */

__attribute__((used)) static const char *kempld_get_type_string(struct kempld_device_data *pld)
{
	const char *version_type;

	switch (pld->info.type) {
	case 0:
		version_type = "release";
		break;
	case 1:
		version_type = "debug";
		break;
	case 2:
		version_type = "custom";
		break;
	default:
		version_type = "unspecified";
		break;
	}

	return version_type;
}