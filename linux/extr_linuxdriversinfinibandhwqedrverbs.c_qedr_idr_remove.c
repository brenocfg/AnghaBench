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
typedef  int /*<<< orphan*/  u32 ;
struct qedr_idr {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  idr; } ;
struct qedr_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedr_idr_remove(struct qedr_dev *dev, struct qedr_idr *qidr, u32 id)
{
	spin_lock_irq(&qidr->idr_lock);
	idr_remove(&qidr->idr, id);
	spin_unlock_irq(&qidr->idr_lock);
}