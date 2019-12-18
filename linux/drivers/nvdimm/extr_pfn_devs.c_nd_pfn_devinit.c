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
struct device {int dummy; } ;
struct nd_pfn {int /*<<< orphan*/  ndns; struct device dev; int /*<<< orphan*/  align; int /*<<< orphan*/  mode; } ;
struct nd_namespace_common {int /*<<< orphan*/  claim; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFN_MODE_NONE ; 
 int /*<<< orphan*/  __nd_attach_ndns (struct device*,struct nd_namespace_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  nd_pfn_default_alignment () ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

struct device *nd_pfn_devinit(struct nd_pfn *nd_pfn,
		struct nd_namespace_common *ndns)
{
	struct device *dev;

	if (!nd_pfn)
		return NULL;

	nd_pfn->mode = PFN_MODE_NONE;
	nd_pfn->align = nd_pfn_default_alignment();
	dev = &nd_pfn->dev;
	device_initialize(&nd_pfn->dev);
	if (ndns && !__nd_attach_ndns(&nd_pfn->dev, ndns, &nd_pfn->ndns)) {
		dev_dbg(&ndns->dev, "failed, already claimed by %s\n",
				dev_name(ndns->claim));
		put_device(dev);
		return NULL;
	}
	return dev;
}