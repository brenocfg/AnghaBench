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
struct stm32_hash_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  dma_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FLAGS_DMA_READY ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stm32_hash_dma_callback(void *param)
{
	struct stm32_hash_dev *hdev = param;

	complete(&hdev->dma_completion);

	hdev->flags |= HASH_FLAGS_DMA_READY;
}