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
struct vsp1_dl_manager {struct vsp1_dl_list* active; } ;
struct vsp1_dl_list {struct vsp1_dl_manager* dlm; } ;

/* Variables and functions */
 int /*<<< orphan*/  vsp1_dl_list_hw_enqueue (struct vsp1_dl_list*) ; 

__attribute__((used)) static void vsp1_dl_list_commit_singleshot(struct vsp1_dl_list *dl)
{
	struct vsp1_dl_manager *dlm = dl->dlm;

	/*
	 * When working in single-shot mode, the caller guarantees that the
	 * hardware is idle at this point. Just commit the head display list
	 * to hardware. Chained lists will be started automatically.
	 */
	vsp1_dl_list_hw_enqueue(dl);

	dlm->active = dl;
}