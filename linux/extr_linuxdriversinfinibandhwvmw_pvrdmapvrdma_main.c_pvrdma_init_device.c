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
struct pvrdma_dev {int /*<<< orphan*/  num_ahs; int /*<<< orphan*/  num_pds; int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  num_srqs; int /*<<< orphan*/  num_qps; int /*<<< orphan*/  cmd_sema; int /*<<< orphan*/  cmd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvrdma_init_device(struct pvrdma_dev *dev)
{
	/*  Initialize some device related stuff */
	spin_lock_init(&dev->cmd_lock);
	sema_init(&dev->cmd_sema, 1);
	atomic_set(&dev->num_qps, 0);
	atomic_set(&dev->num_srqs, 0);
	atomic_set(&dev->num_cqs, 0);
	atomic_set(&dev->num_pds, 0);
	atomic_set(&dev->num_ahs, 0);

	return 0;
}