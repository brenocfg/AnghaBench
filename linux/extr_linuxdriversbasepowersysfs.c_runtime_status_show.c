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
struct device_attribute {int dummy; } ;
struct TYPE_2__ {int runtime_status; scalar_t__ disable_depth; scalar_t__ runtime_error; } ;
struct device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
#define  RPM_ACTIVE 131 
#define  RPM_RESUMING 130 
#define  RPM_SUSPENDED 129 
#define  RPM_SUSPENDING 128 
 int /*<<< orphan*/  sprintf (char*,char const*) ; 

__attribute__((used)) static ssize_t runtime_status_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	const char *p;

	if (dev->power.runtime_error) {
		p = "error\n";
	} else if (dev->power.disable_depth) {
		p = "unsupported\n";
	} else {
		switch (dev->power.runtime_status) {
		case RPM_SUSPENDED:
			p = "suspended\n";
			break;
		case RPM_SUSPENDING:
			p = "suspending\n";
			break;
		case RPM_RESUMING:
			p = "resuming\n";
			break;
		case RPM_ACTIVE:
			p = "active\n";
			break;
		default:
			return -EIO;
		}
	}
	return sprintf(buf, p);
}