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
struct genwqe_file {int /*<<< orphan*/  list; int /*<<< orphan*/  opener; } ;
struct genwqe_dev {int /*<<< orphan*/  file_lock; int /*<<< orphan*/  file_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  task_tgid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void genwqe_add_file(struct genwqe_dev *cd, struct genwqe_file *cfile)
{
	unsigned long flags;

	cfile->opener = get_pid(task_tgid(current));
	spin_lock_irqsave(&cd->file_lock, flags);
	list_add(&cfile->list, &cd->file_list);
	spin_unlock_irqrestore(&cd->file_lock, flags);
}