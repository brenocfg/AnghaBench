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
struct onenand_chip {scalar_t__ state; int /*<<< orphan*/  chip_lock; int /*<<< orphan*/  wq; int /*<<< orphan*/  (* disable ) (struct mtd_info*) ;} ;
struct mtd_info {struct onenand_chip* priv; } ;

/* Variables and functions */
 scalar_t__ FL_PM_SUSPENDED ; 
 scalar_t__ FL_READY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void onenand_release_device(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;

	if (this->state != FL_PM_SUSPENDED && this->disable)
		this->disable(mtd);
	/* Release the chip */
	spin_lock(&this->chip_lock);
	this->state = FL_READY;
	wake_up(&this->wq);
	spin_unlock(&this->chip_lock);
}