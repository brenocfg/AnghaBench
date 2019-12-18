#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct ocrdma_eq {TYPE_1__ q; } ;
struct ocrdma_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ocrdma_destroy_eq (struct ocrdma_dev*,struct ocrdma_eq*) ; 
 int /*<<< orphan*/  free_irq (int,struct ocrdma_eq*) ; 
 int ocrdma_get_irq (struct ocrdma_dev*,struct ocrdma_eq*) ; 
 int /*<<< orphan*/  ocrdma_ring_eq_db (struct ocrdma_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocrdma_destroy_eq(struct ocrdma_dev *dev, struct ocrdma_eq *eq)
{
	int irq;

	/* disarm EQ so that interrupts are not generated
	 * during freeing and EQ delete is in progress.
	 */
	ocrdma_ring_eq_db(dev, eq->q.id, false, false, 0);

	irq = ocrdma_get_irq(dev, eq);
	free_irq(irq, eq);
	_ocrdma_destroy_eq(dev, eq);
}