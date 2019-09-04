#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nand_chip {TYPE_1__* controller; int /*<<< orphan*/  state; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wq; int /*<<< orphan*/ * active; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_READY ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nand_release_device(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	/* Release the controller and the chip */
	spin_lock(&chip->controller->lock);
	chip->controller->active = NULL;
	chip->state = FL_READY;
	wake_up(&chip->controller->wq);
	spin_unlock(&chip->controller->lock);
}