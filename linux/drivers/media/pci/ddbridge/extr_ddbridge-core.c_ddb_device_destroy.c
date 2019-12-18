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
struct ddb {int /*<<< orphan*/  nr; int /*<<< orphan*/  ddb_dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddb_class ; 
 int /*<<< orphan*/  ddb_device_attrs_del (struct ddb*) ; 
 int /*<<< orphan*/  ddb_major ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ddb_device_destroy(struct ddb *dev)
{
	if (IS_ERR(dev->ddb_dev))
		return;
	ddb_device_attrs_del(dev);
	device_destroy(&ddb_class, MKDEV(ddb_major, dev->nr));
}