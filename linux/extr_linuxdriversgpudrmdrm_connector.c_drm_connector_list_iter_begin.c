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
struct drm_device {int dummy; } ;
struct drm_connector_list_iter {int /*<<< orphan*/ * conn; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  connector_list_iter_dep_map ; 
 int /*<<< orphan*/  lock_acquire_shared_recursive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void drm_connector_list_iter_begin(struct drm_device *dev,
				   struct drm_connector_list_iter *iter)
{
	iter->dev = dev;
	iter->conn = NULL;
	lock_acquire_shared_recursive(&connector_list_iter_dep_map, 0, 1, NULL, _RET_IP_);
}