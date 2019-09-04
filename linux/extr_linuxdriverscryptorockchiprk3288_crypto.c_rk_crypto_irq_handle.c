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
typedef  int u32 ;
struct rk_crypto_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  done_task; int /*<<< orphan*/  err; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CRYPTO_READ (struct rk_crypto_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_WRITE (struct rk_crypto_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RK_CRYPTO_INTSTS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct rk_crypto_info* platform_get_drvdata (void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rk_crypto_irq_handle(int irq, void *dev_id)
{
	struct rk_crypto_info *dev  = platform_get_drvdata(dev_id);
	u32 interrupt_status;

	spin_lock(&dev->lock);
	interrupt_status = CRYPTO_READ(dev, RK_CRYPTO_INTSTS);
	CRYPTO_WRITE(dev, RK_CRYPTO_INTSTS, interrupt_status);

	if (interrupt_status & 0x0a) {
		dev_warn(dev->dev, "DMA Error\n");
		dev->err = -EFAULT;
	}
	tasklet_schedule(&dev->done_task);

	spin_unlock(&dev->lock);
	return IRQ_HANDLED;
}