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
struct drm_device {int /*<<< orphan*/  filelist_mutex; } ;
struct drm_client_dev {TYPE_1__* file; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_file_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_client_close(struct drm_client_dev *client)
{
	struct drm_device *dev = client->dev;

	mutex_lock(&dev->filelist_mutex);
	list_del(&client->file->lhead);
	mutex_unlock(&dev->filelist_mutex);

	drm_file_free(client->file);
}