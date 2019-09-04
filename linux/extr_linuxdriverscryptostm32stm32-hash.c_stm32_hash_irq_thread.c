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
struct stm32_hash_dev {int flags; int /*<<< orphan*/  req; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HASH_FLAGS_CPU ; 
 int HASH_FLAGS_DMA_ACTIVE ; 
 int HASH_FLAGS_DMA_READY ; 
 int HASH_FLAGS_OUTPUT_READY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  stm32_hash_finish_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t stm32_hash_irq_thread(int irq, void *dev_id)
{
	struct stm32_hash_dev *hdev = dev_id;

	if (HASH_FLAGS_CPU & hdev->flags) {
		if (HASH_FLAGS_OUTPUT_READY & hdev->flags) {
			hdev->flags &= ~HASH_FLAGS_OUTPUT_READY;
			goto finish;
		}
	} else if (HASH_FLAGS_DMA_READY & hdev->flags) {
		if (HASH_FLAGS_DMA_ACTIVE & hdev->flags) {
			hdev->flags &= ~HASH_FLAGS_DMA_ACTIVE;
				goto finish;
		}
	}

	return IRQ_HANDLED;

finish:
	/* Finish current request */
	stm32_hash_finish_req(hdev->req, 0);

	return IRQ_HANDLED;
}