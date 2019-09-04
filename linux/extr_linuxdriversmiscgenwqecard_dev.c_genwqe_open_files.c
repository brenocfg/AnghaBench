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
struct genwqe_dev {int /*<<< orphan*/  file_lock; int /*<<< orphan*/  file_list; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int genwqe_open_files(struct genwqe_dev *cd)
{
	int rc;
	unsigned long flags;

	spin_lock_irqsave(&cd->file_lock, flags);
	rc = list_empty(&cd->file_list);
	spin_unlock_irqrestore(&cd->file_lock, flags);
	return !rc;
}