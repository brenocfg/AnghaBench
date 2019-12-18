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
struct wcn36xx {int /*<<< orphan*/  hal_ind_lock; int /*<<< orphan*/  hal_ind_queue; int /*<<< orphan*/  hal_ind_work; int /*<<< orphan*/  hal_ind_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_freezable_workqueue (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_ind_smd_work ; 

int wcn36xx_smd_open(struct wcn36xx *wcn)
{
	wcn->hal_ind_wq = create_freezable_workqueue("wcn36xx_smd_ind");
	if (!wcn->hal_ind_wq)
		return -ENOMEM;

	INIT_WORK(&wcn->hal_ind_work, wcn36xx_ind_smd_work);
	INIT_LIST_HEAD(&wcn->hal_ind_queue);
	spin_lock_init(&wcn->hal_ind_lock);

	return 0;
}