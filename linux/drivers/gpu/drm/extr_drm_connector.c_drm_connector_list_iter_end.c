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
struct drm_mode_config {int /*<<< orphan*/  connector_list_lock; } ;
struct drm_connector_list_iter {scalar_t__ conn; TYPE_1__* dev; } ;
struct TYPE_2__ {struct drm_mode_config mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __drm_connector_put_safe (scalar_t__) ; 
 int /*<<< orphan*/  connector_list_iter_dep_map ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void drm_connector_list_iter_end(struct drm_connector_list_iter *iter)
{
	struct drm_mode_config *config = &iter->dev->mode_config;
	unsigned long flags;

	iter->dev = NULL;
	if (iter->conn) {
		spin_lock_irqsave(&config->connector_list_lock, flags);
		__drm_connector_put_safe(iter->conn);
		spin_unlock_irqrestore(&config->connector_list_lock, flags);
	}
	lock_release(&connector_list_iter_dep_map, 0, _RET_IP_);
}