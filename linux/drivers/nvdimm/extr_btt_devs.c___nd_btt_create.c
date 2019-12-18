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
typedef  int /*<<< orphan*/  u8 ;
struct nd_region {int /*<<< orphan*/  btt_ida; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct nd_namespace_common {int /*<<< orphan*/  claim; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * parent; } ;
struct nd_btt {scalar_t__ id; unsigned long lbasize; int /*<<< orphan*/  ndns; struct device dev; int /*<<< orphan*/ * uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __nd_attach_ndns (struct device*,struct nd_namespace_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct nd_btt*) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct nd_btt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_btt_attribute_groups ; 
 int /*<<< orphan*/  nd_btt_device_type ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static struct device *__nd_btt_create(struct nd_region *nd_region,
		unsigned long lbasize, u8 *uuid,
		struct nd_namespace_common *ndns)
{
	struct nd_btt *nd_btt;
	struct device *dev;

	nd_btt = kzalloc(sizeof(*nd_btt), GFP_KERNEL);
	if (!nd_btt)
		return NULL;

	nd_btt->id = ida_simple_get(&nd_region->btt_ida, 0, 0, GFP_KERNEL);
	if (nd_btt->id < 0)
		goto out_nd_btt;

	nd_btt->lbasize = lbasize;
	if (uuid) {
		uuid = kmemdup(uuid, 16, GFP_KERNEL);
		if (!uuid)
			goto out_put_id;
	}
	nd_btt->uuid = uuid;
	dev = &nd_btt->dev;
	dev_set_name(dev, "btt%d.%d", nd_region->id, nd_btt->id);
	dev->parent = &nd_region->dev;
	dev->type = &nd_btt_device_type;
	dev->groups = nd_btt_attribute_groups;
	device_initialize(&nd_btt->dev);
	if (ndns && !__nd_attach_ndns(&nd_btt->dev, ndns, &nd_btt->ndns)) {
		dev_dbg(&ndns->dev, "failed, already claimed by %s\n",
				dev_name(ndns->claim));
		put_device(dev);
		return NULL;
	}
	return dev;

out_put_id:
	ida_simple_remove(&nd_region->btt_ida, nd_btt->id);

out_nd_btt:
	kfree(nd_btt);
	return NULL;
}