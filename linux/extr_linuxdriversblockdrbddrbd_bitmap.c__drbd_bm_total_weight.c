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
struct drbd_bitmap {unsigned long bm_set; int /*<<< orphan*/  bm_lock; struct drbd_bitmap* bm_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  expect (struct drbd_bitmap*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned long _drbd_bm_total_weight(struct drbd_device *device)
{
	struct drbd_bitmap *b = device->bitmap;
	unsigned long s;
	unsigned long flags;

	if (!expect(b))
		return 0;
	if (!expect(b->bm_pages))
		return 0;

	spin_lock_irqsave(&b->bm_lock, flags);
	s = b->bm_set;
	spin_unlock_irqrestore(&b->bm_lock, flags);

	return s;
}