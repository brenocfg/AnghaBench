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
struct ddb {size_t nr; int /*<<< orphan*/  ddb_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DDB_MAX_ADAPTER ; 
 int /*<<< orphan*/  ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,size_t) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddb_class ; 
 int ddb_device_attrs_add (struct ddb*) ; 
 int /*<<< orphan*/  ddb_device_attrs_del (struct ddb*) ; 
 int /*<<< orphan*/  ddb_major ; 
 int /*<<< orphan*/  ddb_mutex ; 
 scalar_t__ ddb_num ; 
 struct ddb** ddbs ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ddb*,char*,size_t) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ddb_device_create(struct ddb *dev)
{
	int res = 0;

	if (ddb_num == DDB_MAX_ADAPTER)
		return -ENOMEM;
	mutex_lock(&ddb_mutex);
	dev->nr = ddb_num;
	ddbs[dev->nr] = dev;
	dev->ddb_dev = device_create(&ddb_class, dev->dev,
				     MKDEV(ddb_major, dev->nr),
				     dev, "ddbridge%d", dev->nr);
	if (IS_ERR(dev->ddb_dev)) {
		res = PTR_ERR(dev->ddb_dev);
		dev_info(dev->dev, "Could not create ddbridge%d\n", dev->nr);
		goto fail;
	}
	res = ddb_device_attrs_add(dev);
	if (res) {
		ddb_device_attrs_del(dev);
		device_destroy(&ddb_class, MKDEV(ddb_major, dev->nr));
		ddbs[dev->nr] = NULL;
		dev->ddb_dev = ERR_PTR(-ENODEV);
	} else {
		ddb_num++;
	}
fail:
	mutex_unlock(&ddb_mutex);
	return res;
}