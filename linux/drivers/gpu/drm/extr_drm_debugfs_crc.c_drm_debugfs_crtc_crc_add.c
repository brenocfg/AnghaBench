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
struct TYPE_2__ {int /*<<< orphan*/  verify_crc_source; int /*<<< orphan*/  set_crc_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_crc_control_fops ; 
 int /*<<< orphan*/  drm_crtc_crc_data_fops ; 

void drm_debugfs_crtc_crc_add(struct drm_crtc *crtc)
{
	struct dentry *crc_ent;

	if (!crtc->funcs->set_crc_source || !crtc->funcs->verify_crc_source)
		return;

	crc_ent = debugfs_create_dir("crc", crtc->debugfs_entry);

	debugfs_create_file("control", S_IRUGO, crc_ent, crtc,
			    &drm_crtc_crc_control_fops);
	debugfs_create_file("data", S_IRUGO, crc_ent, crtc,
			    &drm_crtc_crc_data_fops);
}