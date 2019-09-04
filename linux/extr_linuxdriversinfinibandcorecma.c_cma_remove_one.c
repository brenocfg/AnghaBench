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
struct ib_device {int dummy; } ;
struct cma_device {struct cma_device* default_gid_type; struct cma_device* default_roce_tos; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cma_process_remove (struct cma_device*) ; 
 int /*<<< orphan*/  kfree (struct cma_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cma_remove_one(struct ib_device *device, void *client_data)
{
	struct cma_device *cma_dev = client_data;

	if (!cma_dev)
		return;

	mutex_lock(&lock);
	list_del(&cma_dev->list);
	mutex_unlock(&lock);

	cma_process_remove(cma_dev);
	kfree(cma_dev->default_roce_tos);
	kfree(cma_dev->default_gid_type);
	kfree(cma_dev);
}