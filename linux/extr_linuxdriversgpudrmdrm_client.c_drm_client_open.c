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
struct drm_file {int /*<<< orphan*/  lhead; } ;
struct drm_device {int /*<<< orphan*/  filelist_mutex; int /*<<< orphan*/  filelist_internal; int /*<<< orphan*/  primary; } ;
struct drm_client_dev {struct drm_file* file; struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_file*) ; 
 int PTR_ERR (struct drm_file*) ; 
 struct drm_file* drm_file_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_client_open(struct drm_client_dev *client)
{
	struct drm_device *dev = client->dev;
	struct drm_file *file;

	file = drm_file_alloc(dev->primary);
	if (IS_ERR(file))
		return PTR_ERR(file);

	mutex_lock(&dev->filelist_mutex);
	list_add(&file->lhead, &dev->filelist_internal);
	mutex_unlock(&dev->filelist_mutex);

	client->file = file;

	return 0;
}