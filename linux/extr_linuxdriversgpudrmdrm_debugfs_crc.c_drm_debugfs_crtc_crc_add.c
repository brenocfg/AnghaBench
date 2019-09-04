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
struct drm_crtc {int /*<<< orphan*/  debugfs_entry; TYPE_1__* funcs; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_crc_source; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  drm_crtc_crc_control_fops ; 
 int /*<<< orphan*/  drm_crtc_crc_data_fops ; 

int drm_debugfs_crtc_crc_add(struct drm_crtc *crtc)
{
	struct dentry *crc_ent, *ent;

	if (!crtc->funcs->set_crc_source)
		return 0;

	crc_ent = debugfs_create_dir("crc", crtc->debugfs_entry);
	if (!crc_ent)
		return -ENOMEM;

	ent = debugfs_create_file("control", S_IRUGO, crc_ent, crtc,
				  &drm_crtc_crc_control_fops);
	if (!ent)
		goto error;

	ent = debugfs_create_file("data", S_IRUGO, crc_ent, crtc,
				  &drm_crtc_crc_data_fops);
	if (!ent)
		goto error;

	return 0;

error:
	debugfs_remove_recursive(crc_ent);

	return -ENOMEM;
}