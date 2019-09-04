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
struct drbd_device {struct drbd_bitmap* bitmap; } ;
struct drbd_bitmap {int /*<<< orphan*/  bm_io_wait; int /*<<< orphan*/  bm_change; int /*<<< orphan*/  bm_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct drbd_bitmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int drbd_bm_init(struct drbd_device *device)
{
	struct drbd_bitmap *b = device->bitmap;
	WARN_ON(b != NULL);
	b = kzalloc(sizeof(struct drbd_bitmap), GFP_KERNEL);
	if (!b)
		return -ENOMEM;
	spin_lock_init(&b->bm_lock);
	mutex_init(&b->bm_change);
	init_waitqueue_head(&b->bm_io_wait);

	device->bitmap = b;

	return 0;
}