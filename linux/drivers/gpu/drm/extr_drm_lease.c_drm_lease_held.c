#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_master {TYPE_2__* dev; int /*<<< orphan*/  lessor; } ;
struct drm_file {struct drm_master* master; } ;
struct TYPE_3__ {int /*<<< orphan*/  idr_mutex; } ;
struct TYPE_4__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int _drm_lease_held_master (struct drm_master*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool drm_lease_held(struct drm_file *file_priv, int id)
{
	struct drm_master *master;
	bool ret;

	if (!file_priv || !file_priv->master || !file_priv->master->lessor)
		return true;

	master = file_priv->master;
	mutex_lock(&master->dev->mode_config.idr_mutex);
	ret = _drm_lease_held_master(master, id);
	mutex_unlock(&master->dev->mode_config.idr_mutex);
	return ret;
}