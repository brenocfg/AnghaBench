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
typedef  int /*<<< orphan*/  uint64_t ;
struct qxl_release {int dummy; } ;
struct qxl_device {int /*<<< orphan*/  release_idr_lock; int /*<<< orphan*/  release_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct qxl_release* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct qxl_release *qxl_release_from_id_locked(struct qxl_device *qdev,
						   uint64_t id)
{
	struct qxl_release *release;

	spin_lock(&qdev->release_idr_lock);
	release = idr_find(&qdev->release_idr, id);
	spin_unlock(&qdev->release_idr_lock);
	if (!release) {
		DRM_ERROR("failed to find id in release_idr\n");
		return NULL;
	}

	return release;
}