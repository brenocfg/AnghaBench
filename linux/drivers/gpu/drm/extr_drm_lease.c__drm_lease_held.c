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
struct drm_file {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int _drm_lease_held_master (int /*<<< orphan*/ ,int) ; 

bool _drm_lease_held(struct drm_file *file_priv, int id)
{
	if (!file_priv || !file_priv->master)
		return true;

	return _drm_lease_held_master(file_priv->master, id);
}