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
struct otx2_mbox {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * hwbase; int /*<<< orphan*/ * reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void otx2_mbox_destroy(struct otx2_mbox *mbox)
{
	mbox->reg_base = NULL;
	mbox->hwbase = NULL;

	kfree(mbox->dev);
	mbox->dev = NULL;
}