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
struct allegro_mbox {unsigned int head; unsigned int tail; unsigned int data; size_t size; int /*<<< orphan*/  lock; } ;
struct allegro_dev {int /*<<< orphan*/  sram; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allegro_mbox_init(struct allegro_dev *dev,
			     struct allegro_mbox *mbox,
			     unsigned int base, size_t size)
{
	if (!mbox)
		return -EINVAL;

	mbox->head = base;
	mbox->tail = base + 0x4;
	mbox->data = base + 0x8;
	mbox->size = size;
	mutex_init(&mbox->lock);

	regmap_write(dev->sram, mbox->head, 0);
	regmap_write(dev->sram, mbox->tail, 0);

	return 0;
}