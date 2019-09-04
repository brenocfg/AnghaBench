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
struct rbd_spec {char* pool_id; char* pool_name; scalar_t__ pool_ns; int /*<<< orphan*/  snap_name; int /*<<< orphan*/  snap_id; scalar_t__ image_name; int /*<<< orphan*/  image_id; } ;
struct rbd_device {int /*<<< orphan*/  parent_overlap; struct rbd_spec* parent_spec; struct rbd_device* parent; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct rbd_device* dev_to_rbd_dev (struct device*) ; 
 size_t sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t rbd_parent_show(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	struct rbd_device *rbd_dev = dev_to_rbd_dev(dev);
	ssize_t count = 0;

	if (!rbd_dev->parent)
		return sprintf(buf, "(no parent image)\n");

	for ( ; rbd_dev->parent; rbd_dev = rbd_dev->parent) {
		struct rbd_spec *spec = rbd_dev->parent_spec;

		count += sprintf(&buf[count], "%s"
			    "pool_id %llu\npool_name %s\n"
			    "pool_ns %s\n"
			    "image_id %s\nimage_name %s\n"
			    "snap_id %llu\nsnap_name %s\n"
			    "overlap %llu\n",
			    !count ? "" : "\n", /* first? */
			    spec->pool_id, spec->pool_name,
			    spec->pool_ns ?: "",
			    spec->image_id, spec->image_name ?: "(unknown)",
			    spec->snap_id, spec->snap_name,
			    rbd_dev->parent_overlap);
	}

	return count;
}