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
struct onenand_chip {int /*<<< orphan*/  complete; } ;
struct mtd_info {struct onenand_chip* priv; } ;

/* Variables and functions */
 int onenand_wait (struct mtd_info*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int onenand_interrupt_wait(struct mtd_info *mtd, int state)
{
	struct onenand_chip *this = mtd->priv;

	wait_for_completion(&this->complete);

	return onenand_wait(mtd, state);
}