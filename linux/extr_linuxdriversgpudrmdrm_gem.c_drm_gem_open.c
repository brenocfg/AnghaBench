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
struct drm_file {int /*<<< orphan*/  table_lock; int /*<<< orphan*/  object_idr; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_init_base (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void
drm_gem_open(struct drm_device *dev, struct drm_file *file_private)
{
	idr_init_base(&file_private->object_idr, 1);
	spin_lock_init(&file_private->table_lock);
}