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
typedef  int /*<<< orphan*/  vnr_buf ;
struct drbd_device {int vnr; int minor; struct dentry* debugfs_vol_ed_gen_id; struct dentry* debugfs_vol; struct dentry* debugfs_vol_data_gen_id; struct dentry* debugfs_vol_resync_extents; struct dentry* debugfs_vol_act_log_extents; struct dentry* debugfs_vol_oldest_requests; struct dentry* debugfs_minor; TYPE_1__* resource; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  minor_buf ;
struct TYPE_2__ {int /*<<< orphan*/  name; struct dentry* debugfs_res_volumes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct drbd_device*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_symlink (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_act_log_extents_fops ; 
 int /*<<< orphan*/  device_data_gen_id_fops ; 
 int /*<<< orphan*/  device_ed_gen_id_fops ; 
 int /*<<< orphan*/  device_oldest_requests_fops ; 
 int /*<<< orphan*/  device_resync_extents_fops ; 
 int /*<<< orphan*/  drbd_debugfs_device_cleanup (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_debugfs_minors ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void drbd_debugfs_device_add(struct drbd_device *device)
{
	struct dentry *vols_dir = device->resource->debugfs_res_volumes;
	char minor_buf[8]; /* MINORMASK, MINORBITS == 20; */
	char vnr_buf[8];   /* volume number vnr is even 16 bit only; */
	char *slink_name = NULL;

	struct dentry *dentry;
	if (!vols_dir || !drbd_debugfs_minors)
		return;

	snprintf(vnr_buf, sizeof(vnr_buf), "%u", device->vnr);
	dentry = debugfs_create_dir(vnr_buf, vols_dir);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	device->debugfs_vol = dentry;

	snprintf(minor_buf, sizeof(minor_buf), "%u", device->minor);
	slink_name = kasprintf(GFP_KERNEL, "../resources/%s/volumes/%u",
			device->resource->name, device->vnr);
	if (!slink_name)
		goto fail;
	dentry = debugfs_create_symlink(minor_buf, drbd_debugfs_minors, slink_name);
	kfree(slink_name);
	slink_name = NULL;
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	device->debugfs_minor = dentry;

#define DCF(name)	do {					\
	dentry = debugfs_create_file(#name, 0440,	\
			device->debugfs_vol, device,		\
			&device_ ## name ## _fops);		\
	if (IS_ERR_OR_NULL(dentry))				\
		goto fail;					\
	device->debugfs_vol_ ## name = dentry;			\
	} while (0)

	DCF(oldest_requests);
	DCF(act_log_extents);
	DCF(resync_extents);
	DCF(data_gen_id);
	DCF(ed_gen_id);
#undef DCF
	return;

fail:
	drbd_debugfs_device_cleanup(device);
	drbd_err(device, "failed to create debugfs entries\n");
}