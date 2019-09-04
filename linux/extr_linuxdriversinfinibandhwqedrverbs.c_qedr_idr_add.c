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
typedef  scalar_t__ u32 ;
struct qedr_idr {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  idr; } ;
struct qedr_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc (int /*<<< orphan*/ *,void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedr_idr_add(struct qedr_dev *dev, struct qedr_idr *qidr,
			void *ptr, u32 id)
{
	int rc;

	idr_preload(GFP_KERNEL);
	spin_lock_irq(&qidr->idr_lock);

	rc = idr_alloc(&qidr->idr, ptr, id, id + 1, GFP_ATOMIC);

	spin_unlock_irq(&qidr->idr_lock);
	idr_preload_end();

	return rc < 0 ? rc : 0;
}