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
struct genwqe_file {int /*<<< orphan*/  opener; int /*<<< orphan*/  list; } ;
struct genwqe_dev {int /*<<< orphan*/  file_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int genwqe_del_file(struct genwqe_dev *cd, struct genwqe_file *cfile)
{
	unsigned long flags;

	spin_lock_irqsave(&cd->file_lock, flags);
	list_del(&cfile->list);
	spin_unlock_irqrestore(&cd->file_lock, flags);
	put_pid(cfile->opener);

	return 0;
}