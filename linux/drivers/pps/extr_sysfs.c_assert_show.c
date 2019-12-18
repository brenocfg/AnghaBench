#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nsec; scalar_t__ sec; } ;
struct TYPE_3__ {int mode; } ;
struct pps_device {int /*<<< orphan*/  assert_sequence; TYPE_2__ assert_tu; TYPE_1__ info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PPS_CAPTUREASSERT ; 
 struct pps_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t assert_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct pps_device *pps = dev_get_drvdata(dev);

	if (!(pps->info.mode & PPS_CAPTUREASSERT))
		return 0;

	return sprintf(buf, "%lld.%09d#%d\n",
			(long long) pps->assert_tu.sec, pps->assert_tu.nsec,
			pps->assert_sequence);
}