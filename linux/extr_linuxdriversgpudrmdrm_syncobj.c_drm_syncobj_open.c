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
struct drm_file {int /*<<< orphan*/  syncobj_table_lock; int /*<<< orphan*/  syncobj_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_init_base (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void
drm_syncobj_open(struct drm_file *file_private)
{
	idr_init_base(&file_private->syncobj_idr, 1);
	spin_lock_init(&file_private->syncobj_table_lock);
}