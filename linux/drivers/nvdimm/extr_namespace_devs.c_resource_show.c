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
struct resource {scalar_t__ start; } ;
struct TYPE_2__ {struct resource res; } ;
struct nd_namespace_pmem {TYPE_1__ nsio; } ;
struct nd_namespace_io {struct resource res; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ is_namespace_io (struct device*) ; 
 scalar_t__ is_namespace_pmem (struct device*) ; 
 scalar_t__ resource_size (struct resource*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 struct nd_namespace_io* to_nd_namespace_io (struct device*) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (struct device*) ; 

__attribute__((used)) static ssize_t resource_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct resource *res;

	if (is_namespace_pmem(dev)) {
		struct nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		res = &nspm->nsio.res;
	} else if (is_namespace_io(dev)) {
		struct nd_namespace_io *nsio = to_nd_namespace_io(dev);

		res = &nsio->res;
	} else
		return -ENXIO;

	/* no address to convey if the namespace has no allocation */
	if (resource_size(res) == 0)
		return -ENXIO;
	return sprintf(buf, "%#llx\n", (unsigned long long) res->start);
}