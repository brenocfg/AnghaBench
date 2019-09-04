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
struct kernel_param {int dummy; } ;

/* Variables and functions */
#define  EDAC_REPORTING_DISABLED 130 
#define  EDAC_REPORTING_ENABLED 129 
#define  EDAC_REPORTING_FORCE 128 
 int EINVAL ; 
 int edac_report ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static int edac_report_get(char *buffer, const struct kernel_param *kp)
{
	int ret = 0;

	switch (edac_report) {
	case EDAC_REPORTING_ENABLED:
		ret = sprintf(buffer, "on");
		break;
	case EDAC_REPORTING_DISABLED:
		ret = sprintf(buffer, "off");
		break;
	case EDAC_REPORTING_FORCE:
		ret = sprintf(buffer, "force");
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}