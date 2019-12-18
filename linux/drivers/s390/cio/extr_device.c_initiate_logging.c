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
struct TYPE_2__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct subchannel {TYPE_1__ schid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int chsc_siosl (TYPE_1__) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct subchannel* to_subchannel (struct device*) ; 

__attribute__((used)) static ssize_t
initiate_logging(struct device *dev, struct device_attribute *attr,
		 const char *buf, size_t count)
{
	struct subchannel *sch = to_subchannel(dev);
	int rc;

	rc = chsc_siosl(sch->schid);
	if (rc < 0) {
		pr_warn("Logging for subchannel 0.%x.%04x failed with errno=%d\n",
			sch->schid.ssid, sch->schid.sch_no, rc);
		return rc;
	}
	pr_notice("Logging for subchannel 0.%x.%04x was triggered\n",
		  sch->schid.ssid, sch->schid.sch_no);
	return count;
}