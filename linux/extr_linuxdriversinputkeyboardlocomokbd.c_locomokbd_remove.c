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
struct locomokbd {int /*<<< orphan*/  input; int /*<<< orphan*/  timer; } ;
struct locomo_dev {int /*<<< orphan*/  length; scalar_t__ mapbase; int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct locomokbd*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct locomokbd*) ; 
 struct locomokbd* locomo_get_drvdata (struct locomo_dev*) ; 
 int /*<<< orphan*/  locomo_set_drvdata (struct locomo_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int locomokbd_remove(struct locomo_dev *dev)
{
	struct locomokbd *locomokbd = locomo_get_drvdata(dev);

	free_irq(dev->irq[0], locomokbd);

	del_timer_sync(&locomokbd->timer);

	input_unregister_device(locomokbd->input);
	locomo_set_drvdata(dev, NULL);

	release_mem_region((unsigned long) dev->mapbase, dev->length);

	kfree(locomokbd);

	return 0;
}