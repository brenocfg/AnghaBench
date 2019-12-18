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
 int /*<<< orphan*/  IO_APP_UNITCFG ; 
 int /*<<< orphan*/  IO_SLU_UNITCFG ; 
 int /*<<< orphan*/  __genwqe_readq (struct genwqe_dev*,int /*<<< orphan*/ ) ; 
 struct genwqe_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t version_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	u64 slu_id, app_id;
	struct genwqe_dev *cd = dev_get_drvdata(dev);

	slu_id = __genwqe_readq(cd, IO_SLU_UNITCFG);
	app_id = __genwqe_readq(cd, IO_APP_UNITCFG);

	return sprintf(buf, "%016llx.%016llx\n", slu_id, app_id);
}