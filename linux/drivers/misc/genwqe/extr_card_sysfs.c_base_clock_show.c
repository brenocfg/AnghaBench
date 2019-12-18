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
typedef  int /*<<< orphan*/  u64 ;
struct genwqe_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct genwqe_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  genwqe_base_clock_frequency (struct genwqe_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t base_clock_show(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	u64 base_clock;
	struct genwqe_dev *cd = dev_get_drvdata(dev);

	base_clock = genwqe_base_clock_frequency(cd);
	return sprintf(buf, "%lld\n", base_clock);
}