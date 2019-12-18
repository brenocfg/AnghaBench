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
struct nd_pfn {int /*<<< orphan*/  mode; int /*<<< orphan*/ * uuid; } ;
struct nd_namespace_common {int dummy; } ;
struct nd_btt {int /*<<< orphan*/ * uuid; scalar_t__ lbasize; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_ASYNC ; 
 int /*<<< orphan*/  PFN_MODE_NONE ; 
 int /*<<< orphan*/  __nd_detach_ndns (struct device*,struct nd_namespace_common**) ; 
 scalar_t__ is_idle (struct device*,struct nd_namespace_common*) ; 
 scalar_t__ is_nd_btt (struct device*) ; 
 scalar_t__ is_nd_dax (struct device*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd_device_unregister (struct device*,int /*<<< orphan*/ ) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 
 struct nd_pfn* to_nd_pfn_safe (struct device*) ; 

__attribute__((used)) static void nd_detach_and_reset(struct device *dev,
		struct nd_namespace_common **_ndns)
{
	/* detach the namespace and destroy / reset the device */
	__nd_detach_ndns(dev, _ndns);
	if (is_idle(dev, *_ndns)) {
		nd_device_unregister(dev, ND_ASYNC);
	} else if (is_nd_btt(dev)) {
		struct nd_btt *nd_btt = to_nd_btt(dev);

		nd_btt->lbasize = 0;
		kfree(nd_btt->uuid);
		nd_btt->uuid = NULL;
	} else if (is_nd_pfn(dev) || is_nd_dax(dev)) {
		struct nd_pfn *nd_pfn = to_nd_pfn_safe(dev);

		kfree(nd_pfn->uuid);
		nd_pfn->uuid = NULL;
		nd_pfn->mode = PFN_MODE_NONE;
	}
}