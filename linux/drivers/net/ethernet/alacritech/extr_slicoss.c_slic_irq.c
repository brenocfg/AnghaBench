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
struct slic_shmem_data {int /*<<< orphan*/  isr; } ;
struct slic_shmem {struct slic_shmem_data* shmem_data; } ;
struct slic_device {int /*<<< orphan*/  napi; struct slic_shmem shmem; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SLIC_ICR_INT_MASK ; 
 int /*<<< orphan*/  SLIC_REG_ICR ; 
 int /*<<< orphan*/  SLIC_REG_ISR ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slic_flush_write (struct slic_device*) ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static irqreturn_t slic_irq(int irq, void *dev_id)
{
	struct slic_device *sdev = dev_id;
	struct slic_shmem *sm = &sdev->shmem;
	struct slic_shmem_data *sm_data = sm->shmem_data;

	slic_write(sdev, SLIC_REG_ICR, SLIC_ICR_INT_MASK);
	slic_flush_write(sdev);
	/* make sure sm_data->isr is read after ICR_INT_MASK is set */
	wmb();

	if (!sm_data->isr) {
		dma_rmb();
		/* spurious interrupt */
		slic_write(sdev, SLIC_REG_ISR, 0);
		slic_flush_write(sdev);
		return IRQ_NONE;
	}

	napi_schedule_irqoff(&sdev->napi);

	return IRQ_HANDLED;
}