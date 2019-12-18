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
struct allegro_dev {int /*<<< orphan*/  suballocator; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  allegro_free_buffer (struct allegro_dev*,int /*<<< orphan*/ *) ; 
 int allegro_mcu_disable_interrupts (struct allegro_dev*) ; 
 int allegro_mcu_reset (struct allegro_dev*) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int allegro_mcu_hw_deinit(struct allegro_dev *dev)
{
	int err;

	err = allegro_mcu_reset(dev);
	if (err)
		v4l2_warn(&dev->v4l2_dev,
			  "mcu failed to enter sleep state\n");

	err = allegro_mcu_disable_interrupts(dev);
	if (err)
		v4l2_warn(&dev->v4l2_dev,
			  "failed to disable interrupts\n");

	allegro_free_buffer(dev, &dev->suballocator);

	return 0;
}