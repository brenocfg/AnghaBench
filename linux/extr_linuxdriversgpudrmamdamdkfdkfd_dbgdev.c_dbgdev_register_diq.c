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
struct queue_properties {int /*<<< orphan*/  type; } ;
struct kfd_dbgdev {struct kernel_queue* kq; int /*<<< orphan*/  pqm; int /*<<< orphan*/  dev; } ;
struct kernel_queue {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  KFD_QUEUE_TYPE_DIQ ; 
 int pqm_create_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct queue_properties*,unsigned int*) ; 
 int /*<<< orphan*/  pqm_destroy_queue (int /*<<< orphan*/ ,unsigned int) ; 
 struct kernel_queue* pqm_get_kernel_queue (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int dbgdev_register_diq(struct kfd_dbgdev *dbgdev)
{
	struct queue_properties properties;
	unsigned int qid;
	struct kernel_queue *kq = NULL;
	int status;

	properties.type = KFD_QUEUE_TYPE_DIQ;

	status = pqm_create_queue(dbgdev->pqm, dbgdev->dev, NULL,
				&properties, &qid);

	if (status) {
		pr_err("Failed to create DIQ\n");
		return status;
	}

	pr_debug("DIQ Created with queue id: %d\n", qid);

	kq = pqm_get_kernel_queue(dbgdev->pqm, qid);

	if (!kq) {
		pr_err("Error getting DIQ\n");
		pqm_destroy_queue(dbgdev->pqm, qid);
		return -EFAULT;
	}

	dbgdev->kq = kq;

	return status;
}