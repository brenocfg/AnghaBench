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
struct ocrdma_dev {int /*<<< orphan*/  ibdev; int /*<<< orphan*/  mbx_cmd; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_dev_id ; 

__attribute__((used)) static void ocrdma_remove_free(struct ocrdma_dev *dev)
{

	idr_remove(&ocrdma_dev_id, dev->id);
	kfree(dev->mbx_cmd);
	ib_dealloc_device(&dev->ibdev);
}