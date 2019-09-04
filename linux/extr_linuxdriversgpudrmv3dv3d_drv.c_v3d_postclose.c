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
struct v3d_file_priv {int /*<<< orphan*/ * sched_entity; } ;
struct drm_file {struct v3d_file_priv* driver_priv; } ;
struct drm_device {int dummy; } ;
typedef  enum v3d_queue { ____Placeholder_v3d_queue } v3d_queue ;

/* Variables and functions */
 int V3D_MAX_QUEUES ; 
 int /*<<< orphan*/  drm_sched_entity_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct v3d_file_priv*) ; 

__attribute__((used)) static void
v3d_postclose(struct drm_device *dev, struct drm_file *file)
{
	struct v3d_file_priv *v3d_priv = file->driver_priv;
	enum v3d_queue q;

	for (q = 0; q < V3D_MAX_QUEUES; q++) {
		drm_sched_entity_destroy(&v3d_priv->sched_entity[q]);
	}

	kfree(v3d_priv);
}