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
struct ptp_clock_request {int /*<<< orphan*/  type; } ;
struct ptp_clock_info {int (* enable ) (struct ptp_clock_info*,struct ptp_clock_request*,int) ;} ;
struct ptp_clock {struct ptp_clock_info* info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_TIME ; 
 int EINVAL ; 
 size_t EPERM ; 
 int /*<<< orphan*/  PTP_CLK_REQ_PPS ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct ptp_clock* dev_get_drvdata (struct device*) ; 
 int sscanf (char const*,char*,int*) ; 
 int stub1 (struct ptp_clock_info*,struct ptp_clock_request*,int) ; 

__attribute__((used)) static ssize_t pps_enable_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct ptp_clock *ptp = dev_get_drvdata(dev);
	struct ptp_clock_info *ops = ptp->info;
	struct ptp_clock_request req = { .type = PTP_CLK_REQ_PPS };
	int cnt, enable;
	int err = -EINVAL;

	if (!capable(CAP_SYS_TIME))
		return -EPERM;

	cnt = sscanf(buf, "%d", &enable);
	if (cnt != 1)
		goto out;

	err = ops->enable(ops, &req, enable ? 1 : 0);
	if (err)
		goto out;

	return count;
out:
	return err;
}